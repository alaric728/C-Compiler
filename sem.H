#ifndef __SEM_H
#define __SEM_H

#include "ast.H"
#include <list>
#include <vector>
#include <map>
#include <stack>
#include <assert.h>

namespace llvm {
   class Type;
}

namespace IR {
   class Vtbl;
   class Code;
}

namespace SEM {
  class Type;;
}

void printMe(SEM::Type* t);

namespace SEM {
   using namespace AST;


   class Type {
   public:
      Type() {}
      virtual ~Type() {}
      virtual std::ostream&  print(ostream& os) const { return os;}
      virtual bool accept(Type* t) const { return false;}
      virtual bool isInt() const  { return false;}
      virtual bool isBool() const { return false;}
      virtual bool isVoid() const { return false;}
      virtual bool isError() const { return false;}
      virtual bool isInstance() const { return false;}
      virtual bool isClass() const  { return false;}
      virtual bool isArray() const  { return false;}
      virtual bool isMethod() const { return false;}
      virtual bool isEqual(Type* t) const { return this==t;}
      virtual llvm::Type* getLLVMType(IR::Code&) { return 0;}
      virtual std::string getName() const { return "";}
      friend std::ostream& operator<<(ostream& os,const Type& t) {
         return t.print(os);
      }
   };

   class TypeInt : public Type {
   public:
      TypeInt() {}
      ~TypeInt(){}
      std::ostream&  print(ostream& os) const { return os << "int";}
      std::string getName() const { return "int";}
      bool accept(Type* t) const { return t->isInt() || t->isBool();}
      bool isInt() const  { return true;}
      bool isBool() const { return false;}
      bool isEqual(Type* t) const { return t->isInt();}
      llvm::Type* getLLVMType(IR::Code&);
   };

   class TypeBool : public Type {
   public:
      TypeBool()   {}
      ~TypeBool()  {}
      std::ostream&  print(ostream& os) const { return os << "bool";}
      std::string getName() const { return "bool";}
      bool accept(Type* t) const { return t->isBool();}
      bool isBool() const { return true;}
      bool isEqual(Type* t) const { return t->isBool();}
      llvm::Type* getLLVMType(IR::Code&);
   };

   class TypeVoid : public Type {
   public:
      TypeVoid()  {}
      ~TypeVoid() {}
      std::ostream&  print(ostream& os) const { return os << "void";}
      std::string getName() const { return "void";}
      bool accept(Type* t) const { return t->isVoid();}
      bool isVoid() const { return true;}
      bool isEqual(Type* t) const { return t->isVoid();}
      llvm::Type* getLLVMType(IR::Code&);
   };

   class TypeError : public Type {
   public:
      TypeError()  {}
      ~TypeError() {}
      std::ostream&  print(ostream& os) const { return os << "error";}
      std::string getName() const { return "error";}
      bool accept(Type* t) const { return t->isError();}
      bool isError() const { return true;}
      bool isEqual(Type* t) const { return t->isError();}
   };

   class TypeClass : public Type {
      std::string  _name;
      TypeClass* _parent;
      Scope*      _scope;
      llvm::Type*  _llty;
   public:
      TypeClass(std::string n,TypeClass* p) : _name(n),_parent(p),_scope(0),_llty(0) {}
      ~TypeClass() {}
      void setScope(Scope* s) { _scope = s;}
      Scope* getScope()       { return _scope;}
      SEM::Descriptor* getSymbol(const std::string&  key);
      std::ostream&  print(ostream& os) const;
      bool isClass() const { return true;}
      bool isSuperOf(TypeClass* t2);
      TypeClass* getParent() { return _parent;}
      std::string getName() const { return _name;}
      llvm::Type* getLLVMType(IR::Code&);
      void emitAttributes(IR::Code&,std::vector<llvm::Type*>& att);
      bool hasMethod(string name,TypeMethod* mty);
      MethodDescriptor* getMethod(string name,TypeMethod* mty);
      bool isEqual(Type* t) const;
   };

   class TypeArray : public Type {
      Type* _base;
   public:
      TypeArray(Type* b) : _base(b) {}
      ~TypeArray() {}
      std::ostream&  print(ostream& os) const { 
         return os << "[" << *_base << "]";
      }
      Type* getType() const { return _base;}
      bool isArray() const { return true;}
      bool accept(Type* t) const { 
         return t->isArray() && _base->accept(dynamic_cast<TypeArray*>(t)->getType());
      }
      llvm::Type* getLLVMType(IR::Code&);
      bool isEqual(Type* t) const { 
         if (t->isArray()) {
            TypeArray* t2 = dynamic_cast<TypeArray*>(t);
            if (this == t2)  return true;
            else {
               return _base->isEqual(t2->getType());
            }
         } else return false;
      }
   };

   class TypeInstance : public Type {
      TypeClass* _of;
   public:
      TypeInstance(TypeClass* of) : _of(of) {}
      ~TypeInstance() {}
      TypeClass* getType() { return _of;}
      std::ostream&  print(ostream& os) const { 
         return os << "instance(" << *_of << ")";
      }
      bool isInstance() const { return true;}
      bool accept(Type* t) const { 
         return t->isInstance() && _of->isSuperOf(dynamic_cast<TypeInstance*>(t)->getType());
      }
      llvm::Type* getLLVMType(IR::Code&);
      std::string getName() const { return _of->getName();}
      bool isEqual(Type* t) const { 
         if (t->isInstance()) {
            TypeInstance* t2 = dynamic_cast<TypeInstance*>(t);
            return _of->isEqual(t2->getType());
         } else return false;
      }
   };

   class TypeMethod : public Type {
      TypeClass*             _receiver;
      Type*                        _rt;
      std::vector<Type*>       _fTypes;
      std::vector<std::string> _fNames;
   public:
      TypeMethod(TypeClass* rcv,Type* r) : _receiver(rcv),_rt(r) {}
      void addFormal(std::string n,Type* t) {
         _fTypes.push_back(t);
         _fNames.push_back(n);
      }
      bool isMethod() const { return true;}
      unsigned long nbExpectedArgs()  { return _fNames.size();}
      SEM::Type* acceptCall(std::vector<SEM::Type*>& aty);
      std::string getName() const { return "method!!!";}
      bool canOverride(TypeMethod* t);
      bool isEqual(Type* t) const;
      bool returnsVoid() {
         return _rt->isVoid();
      }
      std::ostream&  print(ostream& os) const { 
         if (_rt)
            os << *_rt << "(";
         else os << "constructor(";
         std::vector<Type*>::const_iterator ti = _fTypes.begin();
         std::vector<std::string>::const_iterator ni = _fNames.begin();
         while (ti != _fTypes.end()) {
            os << (*ti)->getName() << " " << *ni;
            ++ti;
            ++ni;
            if (ti != _fTypes.end())
               os << ",";
         }
         os << ")";
         return os;
      }
      void setFormalNames(llvm::Function* f);
      llvm::Type* getLLVMType(IR::Code&);
   };

   class Descriptor {
   protected:
      Type* _type;
   public:
      Descriptor(Type* t) : _type(t) {}
      Descriptor(const Descriptor& d) : _type(d._type) {}
      Type* getType() { return _type;}
      virtual llvm::Value* get() { return 0;}
      virtual std::ostream& print(std::ostream& os) const {
         return os << *_type;
      }
      friend std::ostream& operator<<(std::ostream& os,const Descriptor& d) {
         return d.print(os);
      }
      virtual bool isField() { return false;}
      virtual bool isMethod() { return false;}
      virtual llvm::Value* genExpr(IR::Code&)    { return 0;}
      virtual llvm::Value* genAddress(IR::Code&) { return 0;}
   };

   class ClassDescriptor : public Descriptor {
      ClassDescriptor* _pClass;
      IR::Vtbl*          _vtbl;
      int                 _nbM;
      llvm::Type*       _cType;
   public:
      ClassDescriptor(Type* t,ClassDescriptor* pCD=0) 
         : Descriptor(t),_pClass(pCD),_nbM(-1),_cType(0) 
      {}
      ClassDescriptor* getParent() { return _pClass;}
      int nbMethods()              { return _nbM;}
      int  labelMethods();
      void makeVTBL(IR::Code&);
      void updateVTBL(int k,llvm::Function* mk);
      void emitVTBL(IR::Code& code);
      IR::Vtbl* patchVTBL();
      void setLLVMType(llvm::Type* ct) { _cType = ct;}
      llvm::Type* getLLVMType()        { return _cType;}
      llvm::Value* getVTBLAddress();
      int requiredSize(IR::Code&);
      std::ostream& print(std::ostream& os) const {
         os << "ClassDesc(#M:" << _nbM << ',';
         if (_pClass) os << *_pClass;
         os << ")";
         return Descriptor::print(os);         
      }
   };

   class MethodDescriptor : public Descriptor {
      ClassDescriptor*   _cd;
      FormalDescriptor* _rec;
      vector<FormalDescriptor*> _args;
      int _offset; // offset within VTBL
   public:
      MethodDescriptor(ClassDescriptor* cd,FormalDescriptor* rec,Type* t) 
         : Descriptor(t),_cd(cd),_rec(rec),_offset(-1) {}
      ClassDescriptor* getClass() { return _cd;}
      std::ostream& print(std::ostream& os) const {
         os << "MethodDesc:";
         return Descriptor::print(os);
      }
      vector<llvm::Type*> getLLVMType(IR::Code&);
      void addFormal(std::string key,FormalDescriptor* fd);
      void setFormalNames(llvm::Function* f);
      void bindFormals(llvm::Function* f);
      void setOffset(int o) { _offset = o;}
      int getOffset() const { return _offset;}
      virtual bool isMethod() { return true;}
      bool returnsVoid() {
         return dynamic_cast<TypeMethod*>(_type)->returnsVoid();
      }
   };

   class FieldDescriptor: public Descriptor {
      int _num;
   public:
      FieldDescriptor(Type* t) : Descriptor(t),_num(0) {}
      std::ostream& print(std::ostream& os) const {
         os << "FieldDesc:";
         return Descriptor::print(os);
      }
      void setFieldNumber(int n) { _num = n;}
      int  getFieldNumber()  { return _num;}
      virtual bool isField() { return true;}
   };

   class FormalDescriptor : public Descriptor {
      llvm::Value* _val;
   public:
      FormalDescriptor(Type* t) : Descriptor(t),_val(0) {}
      void bindTo(llvm::Value* v) { _val = v;}
      llvm::Value* get() { return _val;}
      std::ostream& print(std::ostream& os) const {
         os << "FormalDesc:";
         return Descriptor::print(os);
      }
      llvm::Value* genExpr(IR::Code&);
      llvm::Value* genAddress(IR::Code&);
   };

   class LocalDescriptor : public Descriptor {
      llvm::Value* _val;
   public:
      LocalDescriptor(Type* t) : Descriptor(t) { _val = 0;}
      void bindTo(llvm::Value* v) { _val = v;}
      llvm::Value* get() { return _val;}
      std::ostream& print(std::ostream& os) const {
         os << "LocalDesc:";
         return Descriptor::print(os);
      }
      llvm::Value* genExpr(IR::Code&);
      llvm::Value* genAddress(IR::Code&);
   };

   class Scope {
      std::map<std::string,Descriptor*> _map;
      Scope* _parent;
   public:
      Scope(Scope* p = 0) : _parent(p) {}
      Descriptor* addSymbol(std::string key,Descriptor* d);
      Descriptor* getSymbol(std::string key,bool rec=false);
      friend std::ostream& operator<<(ostream& os,const Scope& s) {
         os << "scope[";
         std::map<std::string,Descriptor*>::const_iterator i = s._map.begin();
         while (i != s._map.end()) {
            os << '\t' << setw(20) << i->first << " --> " << *(i->second) << endl;
            ++i;
         }
         return os << ']' << endl;
      }
      int scanMethods(int lastM,TypeClass* toCheck);
      void scanAttributes(IR::Code& code,std::vector<llvm::Type*>& att);
   };

   class Env {
      stack<Scope*> _env;
      Type *_tint,*_tbool,*_tvoid,*_terror;      
      TypeClass* _currentClass;
      ClassDescriptor* _currentDesc;
      Type* _returnType;
   public:
      Env();
      ~Env();
      Scope* openScope();
      void pushScope(Scope* s);
      Scope* popScope();
      Descriptor* addSymbol(std::string key,Descriptor* d);
      Descriptor* addMethod(std::string key,MethodDescriptor* d);
      Descriptor* getSymbol(std::string key,bool rec=false);      
      void analyze(AST::Node* root);
      void reportError(std::string s);
      void setCurrentClass(TypeClass* cl,ClassDescriptor* cd) { _currentClass = cl;_currentDesc = cd;}
      void setReturnType(Type* rt)           { _returnType = rt;}
      TypeClass* getCurrentClass()           { return _currentClass;}
      ClassDescriptor* getCurrentClassDesc() { return _currentDesc;}
      Type* getReturnType() { return _returnType;}
      Type* getTypeInt()    { return _tint;}
      Type* getTypeBool()   { return _tbool;}
      Type* getTypeVoid()   { return _tvoid;}
      Type* getTypeError()  { return _terror;}      
   };

};

#endif
