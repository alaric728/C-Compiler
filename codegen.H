#ifndef __CODEGEN_H
#define __CODEGEN_H

#include <iostream>
#include <iomanip>
#include <map>
#include <stack>
#include "ast.H"

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/PassManager.h"

namespace llvm {
   class LLVMContext;
   class Module;
   class ExecutionEngine;
   class BasicBlock;
   class Function;
   class GlobalVariable;
}

namespace IR {
   class Code;
   typedef double (*ptrFun)();

   class Vtbl {
      std::vector<llvm::Function*> _tab;
      llvm::ArrayType*              _at; // type of VTBL
      llvm::GlobalVariable*       _glob; // the actual VTBL constant array
   public:
      Vtbl(int sz,IR::Code& code);
      void setMethod(int k,llvm::Function* f) { _tab[k] = f;}
      llvm::Value* emitVTBL(Code& code);
      llvm::Value* getAddress();
      void patchWith(Vtbl* parent);
   };
   
   class Code {
      llvm::LLVMContext& _ctx;
      llvm::Module*      _module;
      llvm::IRBuilder<>* _builder;
      llvm::ExecutionEngine* _engine;
      llvm::FunctionPassManager* _fpm;      
      bool _nob;
      SEM::ClassDescriptor* _cClass;
      std::map<std::string,llvm::Function*> _lib;
   public:
      Code();
      ~Code();
      void dump();
      operator llvm::IRBuilder<>&() { return *_builder;}
      llvm::Module* getModule()     { return _module;}
      
      ptrFun getFPtr(llvm::Function* f);
      void generate(AST::Node* root);
      void noblock()      { _nob = true;}
      bool hasblock()     { return !_nob;}
      void start(llvm::BasicBlock* b);
      void setCurrentClass(SEM::ClassDescriptor* cc) { _cClass = cc;}
      SEM::ClassDescriptor* getCurrentClass() { return _cClass;}
      llvm::Function* getFun(const char* fName); // useful to retrieve a C function with a declaration
      unsigned getSize(llvm::Type* t);
   };
};



#endif
