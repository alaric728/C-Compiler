#include "codegen.H"

#include <iostream>
#include <iomanip>
#include "ast.H"
#include "sem.H"


#include "llvm/Config/llvm-config.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/MCJIT.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/TypeBuilder.h"

#include "llvm/IR/PassManager.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Transforms/Scalar.h"

namespace IR {
   using namespace llvm;
   using namespace std;

   Code::Code()
      : _ctx(getGlobalContext())
   {
      _module = new Module("jit",_ctx);
      _builder = new IRBuilder<>(_ctx);
      InitializeNativeTarget();
      std::unique_ptr<llvm::Module> mPtr(_module);
      EngineBuilder eb(std::move(mPtr));
      _engine = eb.setEngineKind(EngineKind::JIT).create();
      if (!_engine) {
         cout << "couldn't get engine..." << endl; 
         exit(3);
      }
      // _fpm = new FunctionPassManager(_module);
      // // Set up the optimizer pipeline.  Start with registering info about how the
      // // target lays out data structures.
      // _fpm->add(new DataLayout(*_engine->getDataLayout()));
      // // Do simple "peephole" optimizations and bit-twiddling optzns.
      // _fpm->add(createInstructionCombiningPass());
      // // Reassociate expressions.
      // _fpm->add(createReassociatePass());
      // // Eliminate Common SubExpressions.
      // _fpm->add(createGVNPass());
      // // Simplify the control flow graph (deleting unreachable blocks, etc).
      // _fpm->add(createCFGSimplificationPass());
      // _fpm->doInitialization();

      // Create a declaration for malloc and save it in a map for later use.
      llvm::Type* mrt = llvm::PointerType::get(llvm::TypeBuilder<llvm::types::i<8>,true>::get(llvm::getGlobalContext()),0);
      llvm::Type* a0 = llvm::TypeBuilder<llvm::types::i<32>,true>::get(llvm::getGlobalContext());
      ArrayRef<llvm::Type*> mallocArgs(a0);
      //mallocArgs.push_back(a0);
      FunctionType* mallocTy = FunctionType::get(mrt,mallocArgs,false);           
      Function* mallocFun = Function::Create(mallocTy,Function::ExternalLinkage,"malloc",getModule());
      _lib["malloc"] = mallocFun;
   }

   Code::~Code()
   {
      delete _module;
      delete _builder;
   }

   unsigned Code::getSize(llvm::Type* t)
   {
      return _engine->getDataLayout()->getTypeStoreSize(t);
   }

   llvm::Function* Code::getFun(const char* fName) 
   {
      if (_lib.count(fName) > 0)
         return _lib[fName];
      else return 0;
   }

   void Code::start(llvm::BasicBlock* b) 
   { 
      _builder->SetInsertPoint(b);
      _nob=false;
   }

   void Code::dump()
   {
      _module->dump();
   }

   void Code::generate(AST::Node* root)
   {
      root->generate(*this);
      dump();
   }

   Vtbl::Vtbl(int sz,IR::Code& code) 
      : _tab(sz) 
   {
      _at = llvm::ArrayType::get(llvm::PointerType::get(llvm::IntegerType::get(llvm::getGlobalContext(),8),0),_tab.size());
      _glob = new llvm::GlobalVariable(*code.getModule(),_at,true,GlobalValue::ExternalLinkage,0,"vtbl");      
   }
   llvm::Value* Vtbl::getAddress() 
   {
      return _glob;
   }


   llvm::Value* Vtbl::emitVTBL(Code& code)
   {
      std::vector<llvm::Constant*> csts;
      // That's the type of the element (void*)
      llvm::Type* et = llvm::PointerType::get(llvm::TypeBuilder<llvm::types::i<8>,true>::get(llvm::getGlobalContext()),0);
      // Now loop to make the cast on the constants.
      llvm::ConstantFolder cf; // this could be cleaned up
      for(std::vector<llvm::Function*>::iterator i=_tab.begin();i!=_tab.end();i++) {
         llvm::Constant* cc = cf.CreateBitCast(*i,et);
         csts.push_back(cc);
      }
      // Create the array constant
      llvm::Constant* cst = llvm::ConstantArray::get(_at,csts);
      // Add it as a global.
      _glob->setInitializer(cst);
      return _glob;
   }
   
   void Vtbl::patchWith(Vtbl* parent) 
   {      
      for(int k=0;k < _tab.size();k++) 
         if (_tab[k] == 0 && parent)             
            _tab[k] = parent->_tab[k];         
   }

}

namespace SEM {
   // Produce an LLVM Type for the corresponding C-- type (void)
   llvm::Type* TypeVoid::getLLVMType(IR::Code&)
   {
      return llvm::Type::getVoidTy(llvm::getGlobalContext());
   }
   // Produce an LLVM Type for the corresponding C-- type (int)
   llvm::Type* TypeInt::getLLVMType(IR::Code&)
   {
      return llvm::TypeBuilder<llvm::types::i<32>,true>::get(llvm::getGlobalContext());
   }
   // Produce an LLVM Type for the corresponding C-- type (bool)
   llvm::Type* TypeBool::getLLVMType(IR::Code&)
   {
      return llvm::TypeBuilder<llvm::types::i<1>,true>::get(llvm::getGlobalContext());
   }
   
   // Fill a vector of LLVM Types for the class attributes in the  C-- scope (invoked on a class!)
   void Scope::scanAttributes(IR::Code& code,std::vector<llvm::Type*>& att)
   {
      for(std::map<std::string,Descriptor*>::iterator i = _map.begin();i != _map.end();++i) {
         if (i->second->isField()) {
            FieldDescriptor* fd = dynamic_cast<FieldDescriptor*>(i->second);
            fd->setFieldNumber(att.size());
            llvm::Type* fdty = fd->getType()->getLLVMType(code);
            att.push_back(fdty);
         }
      }
   }

   // Fill an LLVM type for a C-- class (traverse the hierarchy too!)
   void TypeClass::emitAttributes(IR::Code& code,std::vector<llvm::Type*>& att)
   {
      if (_parent)
         _parent->emitAttributes(code,att);
      _scope->scanAttributes(code,att);
   }

   // Create and fill (lazily) a vector of LLVM types for a C-- class. 
   // Typical output can be seen on slides L12 , slide 28
   llvm::Type* TypeClass::getLLVMType(IR::Code& code)
   {
      if (_llty)
         return _llty;
      else {
         std::vector<llvm::Type*> attribs;
         llvm::ArrayType* at = llvm::ArrayType::get(llvm::PointerType::get(llvm::IntegerType::get(llvm::getGlobalContext(),8),0),0);
         attribs.push_back(llvm::PointerType::get(at,0));
         emitAttributes(code,attribs);
         llvm::StructType* cty = llvm::StructType::create(llvm::getGlobalContext(),attribs,"Class_"+_name);         
         //llvm::StructType* cty = llvm::StructType::get(llvm::PointerType::get(at,0),attribs);
         _llty = cty;
         //code.getModule()->addTypeName("Class_"+_name,cty);
         cty->setName("Class_" + _name);
         return cty;
      }
   }
   // Create an LLVM type for an Instance type of C-- (i.e., a pointer to the class type!)
   llvm::Type* TypeInstance::getLLVMType(IR::Code& code)
   {
      return llvm::PointerType::get(_of->getLLVMType(code),0);
   }

   llvm::Type* TypeArray::getLLVMType(IR::Code& code) 
   {
      llvm::Type* et = _base->getLLVMType(code);
      return llvm::PointerType::get(et,0);  
   }

   // Create an LLVM type for a method type of C--
   // Don't forget to add the 'hidden' this.
   llvm::Type* TypeMethod::getLLVMType(IR::Code& code)
   {
      std::vector<llvm::Type*> formalsv;
      llvm::Type* myrt = 0;
      if (_rt)
         myrt = _rt->getLLVMType(code);
      else
         myrt = llvm::Type::getVoidTy(llvm::getGlobalContext());
      int k=0;
      for(std::vector<Type*>::iterator i = _fTypes.begin();i!=_fTypes.end();i++) {     
         formalsv.push_back((*i)->getLLVMType(code));
      }
      llvm::ArrayRef<llvm::Type*> formals(formalsv);
      return llvm::FunctionType::get(myrt,formals,false);
   }

   int ClassDescriptor::requiredSize(IR::Code& code)
   {
      unsigned ttl = 8; // 8 bytes for the VPTR (should be made platform dependent)
      std::vector<llvm::Type*> fTypes;
      dynamic_cast<TypeClass*>(_type)->emitAttributes(code,fTypes);
      for(std::vector<llvm::Type*>::iterator i = fTypes.begin(); i != fTypes.end();i++ ) {
         ttl += code.getSize(*i);
      }
      return ttl;
   }

   // Create an empty VTBL and store it in the class descriptor
   void ClassDescriptor::makeVTBL(IR::Code& code) 
   {
      _vtbl = new IR::Vtbl(_nbM,code);
   }
   // update the vtbl with a new value in slot k.
   void ClassDescriptor::updateVTBL(int k,llvm::Function* mk) { 
      _vtbl->setMethod(k,mk);
   }
  
   // Produce the code for the class VTBL (Seen in L12, slides 29-30)
   // You must fill the gaps with methods from the VTBL of the parent (since we inherit).
   // We have to fill missing entries (inherited methods) from the parent's VTBL. 
   void ClassDescriptor::emitVTBL(IR::Code& code)
   {
      patchVTBL();              // fix the gaps (recursively)
      _vtbl->emitVTBL(code);    // dump the actual data definition.
   }
   
   // That's the recursive VTBL fixing. 
   IR::Vtbl* ClassDescriptor::patchVTBL()
   {
      IR::Vtbl* pVtbl = 0;
      if (_pClass) 
         pVtbl = _pClass->patchVTBL();
      _vtbl->patchWith(pVtbl);
      return _vtbl;
   }

   // Retrieves the LLVM value representing the constant VTBL for the class. 
   llvm::Value* ClassDescriptor::getVTBLAddress()
   {
      return _vtbl->getAddress();
   }

   // give names to the argument of a method.
   void TypeMethod::setFormalNames(llvm::Function* f) {
      int k = 0;
      llvm::Function::arg_iterator i = f->arg_begin();
      for(;i != f->arg_end();++i,++k) 
         i->setName(_fNames[k]);     
   }

   // Give names to the arguments of a method (delegate to the type)
   void MethodDescriptor::setFormalNames(llvm::Function* f)
   {
      dynamic_cast<TypeMethod*>(getType())->setFormalNames(f);
   }

   // Build and return a vector of types for the formals appearing in a method/constructor
   // Declaration. This is necessary when declaring a method. 
   vector<llvm::Type*> MethodDescriptor::getLLVMType(IR::Code& code)
   {
      assert(0);
      std::vector<llvm::Type*> frmls;
      std::vector<FormalDescriptor*>::iterator fdi = _args.begin();
      while (fdi != _args.end()) {
         frmls.push_back((*fdi)->getType()->getLLVMType(code));
         ++fdi;
      }
      return frmls;
   }

   // Associate to a FormalDescriptor an LLVM value that
   // will represent the formal in the LLVM output. In this way the
   // body of the method can retrieve the formaldescriptor from the scope
   // and pick up the llvm value for it!
   void MethodDescriptor::bindFormals(llvm::Function* f)
   {
      std::vector<FormalDescriptor*>::iterator fdi = _args.begin();
      llvm::Function::arg_iterator i = f->arg_begin();
      while (fdi!=_args.end()) {
         (*fdi)->bindTo(i);
         ++i;
         ++fdi;
      }   
   }

   llvm::Value* FormalDescriptor::genExpr(IR::Code&)
   {
      return _val;
   }
   llvm::Value* FormalDescriptor::genAddress(IR::Code&)
   {
      return _val;
   }

   llvm::Value* LocalDescriptor::genExpr(IR::Code& code)
   { 
      llvm::IRBuilder<>& build = code;
      return build.CreateLoad(_val,"t");
   }

   llvm::Value* LocalDescriptor::genAddress(IR::Code&) 
   { 
      return _val;
   }
}

namespace AST {
   using namespace llvm;
   // Emit code for the entire program. This implies:
   // 1. Emit code for all the classes
   // 2. Emit the VTBLs for all the classes
   // 3. Emit prototypes of the functions in the C library we wish to call (e.g. malloc)
   // 4. Emit the main entry point (whose job is to allocate a class of type Main and 
   //    call its constructor. 
   void Program::generate(IR::Code& code)
   {
      std::list<Class*>::iterator i = _classes.begin();
      while (i!=_classes.end()) {
         (*i)->generate(code);
         ++i;
      }
      
      // fill/emit all the classes VTBL
      i =  _classes.begin();
      while (i != _classes.end()) {
         (*i)->emitVTBL(code);
         ++i;
      }
      
      Function* mallocFun = code.getFun("malloc");
      // TODO
      // Create a main function that instantiates the Main class.
      IRBuilder<>& build = code;
      _main->emitVTBL(code);
      //Allocate necessary memory for main class
      llvm::Value* size = ConstantInt::get(getGlobalContext(),llvm::APInt(sizeof(int), _main->requiredSize(code)));
      llvm::ArrayRef<llvm::Value*> mallocArgs(size);
      llvm::Value* obj = build.CreateCall(mallocFun, mallocArgs, "t");
      //Arguments
      llvm::ArrayRef<llvm::Value*> args(obj);
      int mOfs = _cstr->getOffset();
      llvm::Value* addrVTBL = _main->getVTBLAddress();
      llvm::Value* basVTBL = build.CreateLoad(addrVTBL, "t");
      llvm::Value* adrEntr = build.CreateConstGEP2_32(basVTBL,0,mOfs,"t");
      llvm::Value* mthPtr = build.CreateLoad(adrEntr, "t");
      llvm::Type* methodType = llvm::PointerType::get(_cstr->getType()->getLLVMType(code),0);
      llvm::Value* f = build.CreateBitCast(mthPtr, methodType, "t");

      //Actual call
      build.CreateCall(f, args, "t");


   }

   // Emit the code for a base class. 
   // 1. Create a VTBL
   // 2. Create a type for the class
   // 3. Create the functions for all the methods.
   void BClass::generate(IR::Code& code)
   {
      //cout << "class " << _id << " has " << _cDesc->nbMethods() << " methods"<< endl;
      _cDesc->makeVTBL(code);
      llvm::Type* cty = _tty->getLLVMType(code);
      _cDesc->setLLVMType(cty);
      for(std::list<Decl*>::iterator i = _decls.begin();i!=_decls.end();++i) {         
         (*i)->generateMethod(code,_cDesc);
      }
   }
   
   // Actually create the VTBL representation.
   void BClass::emitVTBL(IR::Code& code)
   {      
      _cDesc->emitVTBL(code);      
   }

   // Emit the code for a single method. This implies:
   // 1. Make a vector of LLVM types for the formals.
   // 2. Make an LLVM type for the return type
   // 3. Create a method protoype
   // 4. Bind the formals to llvm::value in the FormalDecriptors
   // 5. Create an entry block.
   // 6. Emit the body of the method.
   // 7. Update the VTBL with the newly generated function. 
   llvm::Function* Method::generateMethod(IR::Code& code,SEM::ClassDescriptor* cd)
   {
      vector<llvm::Type*> frmls = _me->getLLVMType(code);
      llvm::Type* rt = _rtty->getLLVMType(code);

      FunctionType* fty = FunctionType::get(rt,frmls,false);
      Function* f = Function::Create(fty,Function::ExternalLinkage,_id,code.getModule());
      _me->setFormalNames(f);      
      _me->bindFormals(f);

      BasicBlock* sb = BasicBlock::Create(getGlobalContext(),"entry",f);
      code.start(sb);
      _body->generate(code);
      if (code.hasblock()) {                   // if a block is still open ... 
         IRBuilder<>& build = code;
         build.CreateRetVoid();      // issue a return instruction
         code.noblock();         // record the fact that there is no "open" block         
      }
      cd->updateVTBL(_me->getOffset(), f);
      verifyFunction(*f);
      return f;
   }

   // Very similar to the method above. 
   llvm::Function* Constructor::generateMethod(IR::Code& code,SEM::ClassDescriptor* cd)
   {
      SEM::TypeMethod* mty = dynamic_cast<SEM::TypeMethod*>(_me->getType());
      llvm::FunctionType* fty = (llvm::FunctionType*)(mty->getLLVMType(code));
      Function* f = Function::Create(fty,Function::ExternalLinkage,_id,code.getModule());
      _me->setFormalNames(f);      
      _me->bindFormals(f);
      BasicBlock* sb = BasicBlock::Create(getGlobalContext(),"entry",f);
      code.start(sb);
      _body->generate(code);
      if (code.hasblock()) {                   // if a block is still open ... 
         IRBuilder<>& build = code;
         build.CreateRetVoid();      // issue a return instruction
         code.noblock();         // record the fact that there is no "open" block         
      }
      cd->updateVTBL(_me->getOffset(), f);
      verifyFunction(*f);
      return f;
   }

   // Bind a formal to an llvm value
   void Formal::bindTo(llvm::Value* v) { 
      _desc->bindTo(v);
   }

   // ======================================================================
   // Expressions ==========================================================

   llvm::Value* Number::genExpr(IR::Code& code) 
   {
      return ConstantInt::get(getGlobalContext(),llvm::APInt(32,_value));
   }

   llvm::Value* Boolean::genExpr(IR::Code& code)
   {
      return ConstantInt::get(getGlobalContext(),llvm::APInt(1,_value));
   }

   llvm::Value* MthCall::genExpr(IR::Code& code)
   {
      //Thanks Greg!
      IRBuilder<>& build = code;
      Expr* rcv = _callee->getReceiver();
      SEM::MethodDescriptor* md = dynamic_cast<SEM::MethodDescriptor*>(_callee->getAttribute());
      //Arguments
      std::vector<llvm::Value*> actuals;
      llvm::Value* obj = rcv->genExpr(code);
      actuals.push_back(obj);
      for(std::list<Expr*>::iterator it = _args.begin(); it != _args.end(); ++it) {
          llvm::Value* a = (*it)->genExpr(code);
          actuals.push_back(a);
      }

      int mOfs = md->getOffset();
      llvm::Value* addrVTBL = build.CreateConstGEP2_32(obj,0,0,"t");
      llvm::Value* basVTBL = build.CreateLoad(addrVTBL, "t");
      llvm::Value* adrEntr = build.CreateConstGEP2_32(basVTBL,0,mOfs,"t");
      llvm::Value* mthPtr = build.CreateLoad(adrEntr, "t");
      llvm::Type* methodType = llvm::PointerType::get(md->getType()->getLLVMType(code),0);
      llvm::Value* f = build.CreateBitCast(mthPtr, methodType, "t");
      ArrayRef<llvm::Value*> args(actuals);
      //Actual call
      return build.CreateCall(f,  args, "t");
   }

   llvm::Value* Opposite::genExpr(IR::Code& code)
   {
      llvm::Value* a = _op->genExpr(code);
      IRBuilder<>& build = code;
      llvm::Value* res = build.CreateNeg(a, "t");
      return res;
   }
   
   llvm::Value* Not::genExpr(IR::Code& code)
   {
      llvm::Value* a = _op->genExpr( code);
      IRBuilder<>& build = code;
      llvm::Value* res = build.CreateNot(a, "t");
      return res;
   }

   llvm::Value* Add::genExpr(IR::Code& code) 
   { 
      llvm::Value* a = _left->genExpr(code);
      llvm::Value* b = _right->genExpr(code);
      IRBuilder<>& build = code;
      llvm::Value* c = build.CreateAdd(a,b,"t");
      return c;
   }

   llvm::Value* Sub::genExpr(IR::Code& code) 
   { 
      llvm::Value* a = _left->genExpr(code);
      llvm::Value* b = _right->genExpr(code);
      IRBuilder<>& build = code;
      llvm::Value* c = build.CreateSub(a,b,"t");
      return c;
   }

   llvm::Value* Mul::genExpr(IR::Code& code) 
   { 
      llvm::Value* a = _left->genExpr(code);
      llvm::Value* b = _right->genExpr(code);
      IRBuilder<>& build = code;
      llvm::Value* c = build.CreateMul(a,b,"t");
      return c;
   }

   llvm::Value* Div::genExpr(IR::Code& code) 
   { 
      llvm::Value* a = _left->genExpr(code);
      llvm::Value* b = _right->genExpr(code);
      IRBuilder<>& build = code;
      llvm::Value* c = build.CreateSDiv(a,b,"t");
      return c;
   }

   llvm::Value* LThen::genExpr(IR::Code& code) 
   { 
      llvm::Value* a = _left->genExpr(code);
      llvm::Value* b = _right->genExpr(code);
      IRBuilder<>& build = code;
      llvm::Value* c = build.CreateICmpSLT(a,b,"t");
      return c;
   }

   llvm::Value* LEThen::genExpr(IR::Code& code) 
   { 
      llvm::Value* a = _left->genExpr(code);
      llvm::Value* b = _right->genExpr(code);
      IRBuilder<>& build = code;
      llvm::Value* c = build.CreateICmpSLE(a,b,"t");
      return c;
   }

   llvm::Value* GThen::genExpr(IR::Code& code) 
   { 
      llvm::Value* a = _left->genExpr(code);
      llvm::Value* b = _right->genExpr(code);
      IRBuilder<>& build = code;
      llvm::Value* c = build.CreateICmpSGT(a,b,"t");
      return c;
   }

   llvm::Value* GEThen::genExpr(IR::Code& code) 
   { 
      llvm::Value* a = _left->genExpr(code);
      llvm::Value* b = _right->genExpr(code);
      IRBuilder<>& build = code;
      llvm::Value* c = build.CreateICmpSGE(a,b,"t");
      return c;
   }

   llvm::Value* Equal::genExpr(IR::Code& code) 
   { 
      llvm::Value* a = _left->genExpr(code);
      llvm::Value* b = _right->genExpr(code);
      IRBuilder<>& build = code;
      llvm::Value* c = build.CreateICmpEQ(a,b,"t");
      return c;
   }

   llvm::Value* NEqual::genExpr(IR::Code& code) 
   { 
      llvm::Value* a = _left->genExpr(code);
      llvm::Value* b = _right->genExpr(code);
      IRBuilder<>& build = code;
      llvm::Value* c = build.CreateICmpNE(a,b,"t");
      return c;
   }

   llvm::Value* And::genExpr(IR::Code& code)  // left && right
   {
      IRBuilder<>& build = code;
      //We generate our new function
      llvm::Function* f = build.GetInsertBlock()->getParent();
      //Create basic blocks for if,else and merge any current open blocks
      BasicBlock* startb = BasicBlock::Create(getGlobalContext(),"startb",f);
      BasicBlock* nextb = BasicBlock::Create(getGlobalContext(),"nextb",f);
      BasicBlock* exitb = BasicBlock::Create(getGlobalContext(), "exitb",f);
      BasicBlock* mb = 0;
      
      code.start(startb);
      llvm::Value* cond1 = _left->genExpr(code);
      //If first condition is false short circuit to end
      build.CreateCondBr(cond1,nextb,exitb);
      startb = build.GetInsertBlock();
      code.start(nextb);
      //Generate testing second condition code
      llvm::Value* cond2 = _right->genExpr(code);
      build.CreateBr(exitb);
      nextb = build.GetInsertBlock();
      //Start up the exit block
      code.start(exitb);
      llvm::PHINode* result = build.CreatePHI(cond1->getType(), 2);
      result->addIncoming(cond1, startb);
      result->addIncoming(cond2, nextb);
      if (code.hasblock()) {
          if (!mb)
              mb = BasicBlock::Create(getGlobalContext(), "mergeb", f);
          build.CreateBr(mb);
      }
      exitb = build.GetInsertBlock();
      
      //Resume any block we may have interrupted
      if (mb)
          code.start(mb);

      return result;
   }

   llvm::Value* Or::genExpr(IR::Code& code) 
   { 
      IRBuilder<>& build = code;
      //We generate our new function
      llvm::Function* f = build.GetInsertBlock()->getParent();
      //Create basic blocks for if,else and merge any current open blocks
      BasicBlock* startb = BasicBlock::Create(getGlobalContext(),"startb",f);
      BasicBlock* nextb = BasicBlock::Create(getGlobalContext(),"nextb",f);
      BasicBlock* exitb = BasicBlock::Create(getGlobalContext(), "exitb",f);
      BasicBlock* mb = 0;
      
      code.start(startb);
      llvm::Value* cond1 = _left->genExpr(code);
      //If first condition is false short circuit to end
      build.CreateCondBr(cond1,exitb,nextb);
      startb = build.GetInsertBlock();
      code.start(nextb);
      //Generate testing second condition code
      llvm::Value* cond2 = _right->genExpr(code);
      build.CreateBr(exitb);
      nextb = build.GetInsertBlock();
      //Start up the exit block
      code.start(exitb);
      llvm::PHINode* result = build.CreatePHI(cond1->getType(), 2);
      result->addIncoming(cond1, startb);
      result->addIncoming(cond2, nextb);
      if (code.hasblock()) {
          if (!mb)
              mb = BasicBlock::Create(getGlobalContext(), "mergeb", f);
          build.CreateBr(mb);
      }
      exitb = build.GetInsertBlock();
      
      //Resume any block we may have interrupted
      if (mb)
          code.start(mb);

      return result;
   }

   llvm::Value* InstantiateObject::genExpr(IR::Code& code) 
   {
      IRBuilder<>& build = code;
      //Malloc Call
      llvm::Function* fmalloc = code.getFun("malloc");
      llvm::Value* size = ConstantInt::get(getGlobalContext(),llvm::APInt(sizeof(int), _desc->requiredSize(code)));
      llvm::ArrayRef<llvm::Value*> mallocArgs(size);
      llvm::Value* obj = build.CreateCall(fmalloc, mallocArgs, "t");
      //Arguments
      std::vector<llvm::Value*> actuals;
      actuals.push_back(obj);
      for(std::list<Expr*>::iterator it = _args.begin(); it != _args.end(); ++it) {
          llvm::Value* a = (*it)->genExpr(code);
          actuals.push_back(a);
      }

      int mOfs = _mdesc->getOffset();
      llvm::Value* addrVTBL = _desc->getVTBLAddress();
      llvm::Value* basVTBL = build.CreateLoad(addrVTBL, "t");
      llvm::Value* adrEntr = build.CreateConstGEP2_32(basVTBL,0,mOfs,"t");
      llvm::Value* mthPtr = build.CreateLoad(adrEntr, "t");
      llvm::Type* methodType = llvm::PointerType::get(_mdesc->getType()->getLLVMType(code),0);
      llvm::Value* f = build.CreateBitCast(mthPtr, methodType, "t");

      //Actual call
      ArrayRef<llvm::Value*> args(actuals);
      llvm::Value* result = build.CreateCall(f, args, "t");
      return result;
   }

   llvm::Value* InstantiateArray::genExpr(IR::Code& code)
   {
       IRBuilder<>& build = code;
       llvm::Value* size = _args->genExpr(code);
       int typeSize = code.getSize(_at->getLLVMType(code));
       llvm::Value* sizeOfType = ConstantInt::get(getGlobalContext(), llvm::APInt(sizeof(int), typeSize));
       llvm::Value* sizeOfInt = ConstantInt::get(getGlobalContext(),llvm::APInt(sizeof(int),sizeof(int)));
       size = build.CreateMul(size, sizeOfType);
       llvm::Value* actualSize = build.CreateAdd(size, sizeOfInt);
       llvm::Function* fmalloc = code.getFun("malloc");
       llvm::ArrayRef<llvm::Value*> mallocArgs(actualSize);
       llvm::Value* baseAddr = build.CreateCall(fmalloc, mallocArgs, "t");
       build.CreateStore(size, baseAddr);
       return baseAddr;
   }

   llvm::Value* Deref::genExpr(IR::Code& code) 
   {
      IRBuilder<>& build = code;
      llvm::Value* obj = _obj->genExpr(code);
      int fn = dynamic_cast<SEM::FieldDescriptor*>(_aDesc)->getFieldNumber();
      llvm::Value* adrField = build.CreateConstGEP2_32(obj,0,fn,"t");
      return build.CreateLoad(adrField,"t");      
   }

   llvm::Value* Deref::genAddress(IR::Code& code)
   {
      IRBuilder<>& build = code;
      llvm::Value* obj = _obj->genExpr(code);
      int fn = dynamic_cast<SEM::FieldDescriptor*>(_aDesc)->getFieldNumber();
      llvm::Value* adrField = build.CreateConstGEP2_32(obj,0,fn,"t");
      return adrField;
   }

   llvm::Value* ArrayIndex::genExpr(IR::Code& code)
   {
      IRBuilder<>& build = code;
      llvm::Value* offset = ConstantInt::get(getGlobalContext(),llvm::APInt(sizeof(int),sizeof(int)));
      llvm::Value* ind = _index->genExpr(code);
      llvm::Value* addr = _array->genExpr(code);
      llvm::Value* gep = build.CreateGEP(addr, ind, "t");
      llvm::Value* ptr = build.CreateAdd(gep, offset, "t");
      llvm::Value* result = build.CreateLoad(ptr, "t");
      return result;
   }

   llvm::Value* ArrayIndex::genAddress(IR::Code& code)
   { 
      IRBuilder<>& build = code;
      llvm::Value* ind = _index->genExpr(code);
      llvm::Value* addr = _array->genExpr(code);
      llvm::Value* gep = build.CreateGEP(addr, ind, "t");
      llvm::Value* offset = ConstantInt::get(getGlobalContext(),llvm::APInt(sizeof(int),sizeof(int)));
      llvm::Value* ptr = build.CreateAdd(gep, offset, "t");
      return ptr;
   }

   llvm::Value* Identifier::genExpr(IR::Code& code)
   {
      if (_oDesc) {
         IRBuilder<>& build = code;
         llvm::Value* ov = _oDesc->genExpr(code);
         int fn = dynamic_cast<SEM::FieldDescriptor*>(_desc)->getFieldNumber();
         llvm::Value* adrField = build.CreateConstGEP2_32(ov,0,fn,"t");
         return build.CreateLoad(adrField,"t");
      } else {
         return _desc->genExpr(code);
      }
   }
   
   llvm::Value* Identifier::genAddress(IR::Code& code)
   {
      if (_oDesc) {
         IRBuilder<>& build = code;
         llvm::Value* ov = _oDesc->genExpr(code);
         int fn = dynamic_cast<SEM::FieldDescriptor*>(_desc)->getFieldNumber();
         llvm::Value* adrField = build.CreateConstGEP2_32(ov,0,fn,"t");
         return adrField;
      } else
         return _desc->genAddress(code);
   }


   // ======================================================================
   // Statements ===========================================================

   void Block::generate(IR::Code& code)
   {
      for(std::list<Stmt*>::iterator i=_body.begin();i!=_body.end();++i) {
         (*i)->generate(code);
      }
   }

   void StmtExpr::generate(IR::Code& code)
   {
      IRBuilder<>& build = code;
      _expr->genExpr(code);
   }

   void StmtLocalDecl::generate(IR::Code& code)
   {
      IRBuilder<>& build = code;
      llvm::Type* type = _desc->getType()->getLLVMType(code);
      llvm::AllocaInst* baseAd =  build.CreateAlloca(type);
      _desc->bindTo(baseAd);
   }

   void StmtAssign::generate(IR::Code& code)
   {
      IRBuilder<>& build = code;
      llvm::Value* l = _lv->genAddress(code);
      llvm::Value* r = _expr->genExpr(code);
      build.CreateStore(r,l);
   }

   void While::generate(IR::Code& code)
   {
      IRBuilder<>& build = code;
      llvm::Function* f = build.GetInsertBlock()->getParent();
      BasicBlock* tb = BasicBlock::Create(getGlobalContext(), "trueb", f);
      BasicBlock* contb = BasicBlock::Create(getGlobalContext(), "contb", f);
      BasicBlock* exitb = BasicBlock::Create(getGlobalContext(), "exitb", f);
      BasicBlock* mb = 0;
      code.start(contb);
      llvm::Value* cv = _cond->genExpr(code);
      build.CreateCondBr(cv, tb, exitb);
      code.start(tb);
      _body->generate(code);
      build.CreateBr(contb);
     
      tb = build.GetInsertBlock();
      code.start(exitb);
      if (code.hasblock()) {
          if (!mb)
              mb = BasicBlock::Create(getGlobalContext(), "mergeb", f);
	  build.CreateBr(mb);
      }
      exitb = build.GetInsertBlock();
      if (mb)
          code.start(mb);

   }

   void IfTE::generate(IR::Code& code)
   {      
      IRBuilder<>& build = code;
      //We generate our new function
      llvm::Function* f = build.GetInsertBlock()->getParent();
      //Create basic blocks for if,else and merge any current open blocks
      BasicBlock* tb = BasicBlock::Create(getGlobalContext(),"trueb",f);
      BasicBlock* fb = BasicBlock::Create(getGlobalContext(),"falseb",f);
      BasicBlock* mb = 0;
      //Evaluate our condition
      llvm::Value* cv = _cond->genExpr(code);
      //Create our branch condition with the appropriate labels
      build.CreateCondBr(cv,tb,fb);
      //Emit the label for true branch
      code.start(tb);
      //Generate true branch code
      _tb->generate(code);
      if (code.hasblock()) {   //Handle block merging
          mb = BasicBlock::Create(getGlobalContext(),"mergeb",f);
          build.CreateBr(mb);
      }
      tb = build.GetInsertBlock();
      //Start up the false block
      code.start(fb);
      if (_eb) { //If no false block, do not generate code.
          _eb->generate(code);
      }
      if (code.hasblock()) {
          if (!mb)
              mb = BasicBlock::Create(getGlobalContext(), "mergeb", f);
          build.CreateBr(mb);
      }
      fb = build.GetInsertBlock();
      
      //Resume any block we may have interrupted
      if (mb)
          code.start(mb);
   }
 
   void Return::generate(IR::Code& code)
   {
      IRBuilder<>& build = code;
      if (_ret) 
         build.CreateRet(_ret->genExpr(code));
      build.CreateRetVoid();
   }
}
