#ifndef __AST_H
#define __AST_H

#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include <stdlib.h>

namespace SEM {
   class Type;
   class TypeClass;
   class TypeMethod;
   class TypeArray;
   class Descriptor;
   class ClassDescriptor;
   class MethodDescriptor;
   class FormalDescriptor;
   class LocalDescriptor;
   class Env;
   class Scope;
}

namespace IR {
   class Code;
}

namespace llvm {
   class Value;
   class Function;
}

namespace AST {
   using namespace std;
   class Node {
   public:
      Node();
      virtual ~Node();
      virtual ostream& print(ostream& os) const = 0;
      virtual void generate(IR::Code&) {}
      virtual void emitVTBL(IR::Code&) {}
      virtual void semPass0(SEM::Env& env) {}
      virtual void semPass1(SEM::Env& env) {}
      virtual void semPass2(SEM::Env& env) {}
      virtual void semPass3(SEM::Env& env) {}
      virtual SEM::Type* semType(SEM::Env& env) { return 0;}
   };
   
   class Expr : public Node {
   protected:
      SEM::Type* _theType;
   public:
      Expr() : Node() { _theType = 0;}
      virtual llvm::Value* genExpr(IR::Code&)    { return 0;}
      virtual llvm::Value* genAddress(IR::Code&) { return 0;}      
      void generate(IR::Code&) {}
      virtual Expr* getReceiver() { return 0;}
      virtual SEM::Descriptor* getAttribute() { return 0;}
      virtual SEM::Type* getType() { return _theType;}
   };

   class Opposite : public Expr {
      Expr* _op;
   public:
      Opposite(Expr* op) : _op(op) {}
      ostream& print(ostream& os) const { 
         os << '-';
         _op->print(os);
         return os;
      }
      SEM::Type* semType(SEM::Env& env);
      llvm::Value* genExpr(IR::Code&);
   };

   class Not : public Expr {
      Expr* _op;
   public:
      Not(Expr* op) : _op(op) {}
      ostream& print(ostream& os) const { 
         os << '!';
         _op->print(os);
         return os;
      }
      SEM::Type* semType(SEM::Env& env);
      llvm::Value* genExpr(IR::Code&);
   };

   class Binary : public Expr {
   protected:
      Expr* _left;
      Expr* _right;
      virtual const char* opName() const = 0;
   public:
      Binary(Expr* l,Expr* r) : _left(l),_right(r) {}      
      ostream& print(ostream& os) const;
      SEM::Type* semType(SEM::Env& env);
   };
   
   class Add : public Binary {
      const char* opName() const { return "+";}
   public:
      Add(Expr* l,Expr* r) : Binary(l,r) {}
      llvm::Value* genExpr(IR::Code&);
   };

   class Sub : public Binary {
      const char* opName() const { return "-";}
   public:
      Sub(Expr* l,Expr* r) : Binary(l,r) {}
      llvm::Value* genExpr(IR::Code&);
   };

   class Mul : public Binary {
      const char* opName() const { return "*";}
   public:
      Mul(Expr* l,Expr* r) : Binary(l,r) {}
      llvm::Value* genExpr(IR::Code&);
   };

   class Div : public Binary {
      const char* opName() const { return "/";}
   public:
      Div(Expr* l,Expr* r) : Binary(l,r) {}
      llvm::Value* genExpr(IR::Code&);
   };

   class Relational : public Binary {
   public:
      Relational(Expr* l,Expr* r) : Binary(l,r) {}
      SEM::Type* semType(SEM::Env& env);
   };

   class LThen : public Relational {
      const char* opName() const { return "<";}
   public:
      LThen(Expr* l,Expr* r) : Relational(l,r) {}
      llvm::Value* genExpr(IR::Code&);
   };

   class LEThen : public Relational {
      const char* opName() const { return "<=";}
   public:
      LEThen(Expr* l,Expr* r) : Relational(l,r) {}
      llvm::Value* genExpr(IR::Code&);
   };

   class GThen : public Relational {
      const char* opName() const { return ">";}
   public:
      GThen(Expr* l,Expr* r) : Relational(l,r) {}
      llvm::Value* genExpr(IR::Code&);
   };

   class GEThen : public Relational {
      const char* opName() const { return ">=";}
   public:
      GEThen(Expr* l,Expr* r) : Relational(l,r) {}
      llvm::Value* genExpr(IR::Code&);
   };
   
   class Equal : public Relational {
      const char* opName() const { return "==";}
   public:
      Equal(Expr* l,Expr* r) : Relational(l,r) {}
      llvm::Value* genExpr(IR::Code&);
   };

   class NEqual : public Relational {
      const char* opName() const { return "!=";}
   public:
      NEqual(Expr* l,Expr* r) : Relational(l,r) {}
      llvm::Value* genExpr(IR::Code&);
   };

   class And : public Binary {
      const char* opName() const { return "&&";}
   public:
      And(Expr* l,Expr* r) : Binary(l,r) {}
      llvm::Value* genExpr(IR::Code&);
      SEM::Type* semType(SEM::Env& env);
   };

   class Or : public Binary {
      const char* opName() const { return "||";}
   public:
      Or(Expr* l,Expr* r) : Binary(l,r) {}
      llvm::Value* genExpr(IR::Code&);
      SEM::Type* semType(SEM::Env& env);
   };
   
   class Identifier : public Expr {
      std::string _value;
      SEM::Descriptor* _desc;
      SEM::Descriptor* _oDesc;
   public:
      Identifier() : _value("lambda"),_desc(0),_oDesc(0)   {}
      Identifier(char* s) : _value(s),_desc(0),_oDesc(0)   {  free(s);}      
      Identifier(const char* s) : _value(s),_desc(0),_oDesc(0) {}      
      const std::string& get() { return _value;}
      ostream& print(ostream& os) const;
      SEM::Type* semType(SEM::Env& env);
      llvm::Value* genExpr(IR::Code&);
      llvm::Value* genAddress(IR::Code&);
   };

   class Number : public Expr {
   protected:
      int _value;
   public:
      Number(int v) : _value(v) {}
      ostream& print(ostream& os) const {
         return os << _value;
      }
      llvm::Value* genExpr(IR::Code&);
      SEM::Type* semType(SEM::Env& env);
   };

   class Boolean : public Number {
   public:
      Boolean(bool v) : Number(v) {}
      ostream& print(ostream& os) const {
         return os << "bool:" << _value;
      }
      SEM::Type* semType(SEM::Env& env);
      llvm::Value* genExpr(IR::Code&);
   };
   
   class Deref : public Expr {
      Expr*         _obj;
      std::string  _name; // field or method name
      SEM::Descriptor* _aDesc; 
   public:
      Deref(Expr* e,char* f) : _obj(e),_name(f),_aDesc(0) { free(f);}
      Deref(Expr* e,const std::string& f) : _obj(e),_name(f),_aDesc(0) {}
      ostream& print(ostream& os) const {
         _obj->print(os);
         return os << '.' << _name;                 
      }      
      SEM::Type* semType(SEM::Env& env);
      Expr* getReceiver() { return _obj;}
      SEM::Descriptor* getAttribute() { return _aDesc;}
      llvm::Value* genExpr(IR::Code&);
      llvm::Value* genAddress(IR::Code&);
   };

   class ArrayIndex : public Expr {
      Expr* _array;
      Expr* _index;
   public:
      ArrayIndex(Expr* a,Expr* i) : _array(a),_index(i) {}
      ostream& print(ostream& os) const {
         _array->print(os);
         os << '[';
         _index->print(os);
         return os << ']';
      }
      SEM::Type* semType(SEM::Env& env);
      llvm::Value* genExpr(IR::Code&);
      llvm::Value* genAddress(IR::Code&);
   };

   class MthCall : public Expr {
      Expr*            _callee;
      Expr*            _rcv;
      std::list<Expr*> _args;
   public:
      MthCall(Expr* c,std::list<Expr*>* la) 
         : _callee(c),_args(*la) {
         delete la; // we stored a copy of the list. 
         _rcv = 0;
         if (dynamic_cast<Deref*>(c) == 0) {
            Identifier* mName = dynamic_cast<Identifier*>(_callee);
            _callee = new Deref(new Identifier("this"),mName->get());
         }
      }
      ~MthCall() {}
      ostream& print(ostream& os) const;
      SEM::Type* semType(SEM::Env& env);
      llvm::Value* genExpr(IR::Code&);
   };
   
   class InstantiateObject : public Expr {
      Identifier*           _class;
      std::list<Expr*>       _args;
      SEM::ClassDescriptor*  _desc;
      SEM::MethodDescriptor* _mdesc;
   public:
      InstantiateObject(Identifier* cl,std::list<Expr*>* la) 
         : _class(cl),_args(*la),_desc(0),_mdesc(0) {}
      ~InstantiateObject() {}
      ostream& print(ostream& os) const {
         os << "new ";
         _class->print(os);
         os << '(';
         for(std::list<Expr*>::const_iterator i = _args.begin();i!=_args.end();++i) {
            os << *i;
            os << ',';
         }
         return os << ')';
      }  
      SEM::Type* semType(SEM::Env& env);
      llvm::Value* genExpr(IR::Code&);
   };
   
   class Type :public Node {
   public:
      Type() {}
      ostream& print(ostream& os) const { return os;}
   };

   class InstantiateArray : public Expr {
      Type* _type;
      Expr* _args;      
      SEM::TypeArray* _at;
   public: 
      InstantiateArray(Type* t,Expr* actual)
         : _type(t),_args(actual) {}
      ~InstantiateArray() {}
      ostream& print(ostream& os) const {
         os << "new ";
         _type->print(os);
         os << '[';
         _args->print(os);
         return os << ']';
      }      
      SEM::Type* semType(SEM::Env& env);      
      llvm::Value* genExpr(IR::Code&);
   };

   class Decl :public Node {
   public:
      Decl() {}
      ostream& print(ostream& os) const { return os;}
      virtual void semFormalMethod(SEM::MethodDescriptor* m,SEM::Env& env) {}
      virtual llvm::Function* generateMethod(IR::Code& code,SEM::ClassDescriptor* cd) { return 0;}
      virtual void setNameFor(llvm::Value*) {}
   };


   class Class :public Node {
   public:
      Class() {}
      ostream& print(ostream& os) const { return os;}
   };

   class Stmt :public Node {
   public:
      Stmt() {}
      ostream& print(ostream& os) const { return os;}
   };

   class TypeInt : public Type {
   public:
      TypeInt() {}
      ostream& print(ostream& os) const { return os << "int";}
      SEM::Type* semType(SEM::Env& env);
   };

   class TypeBool : public Type {
   public:
      TypeBool() {}
      ostream& print(ostream& os) const { return os << "bool";}
      SEM::Type* semType(SEM::Env& env);
   };

   class TypeVoid : public Type {
   public:
      TypeVoid() {}
      ostream& print(ostream& os) const { return os << "void";}
      SEM::Type* semType(SEM::Env& env);
   };

   class TypeClass : public Type {
      Identifier* _cName;
   public:
      TypeClass(Identifier* cn) : _cName(cn) {}
      ostream& print(ostream& os) const { 
         os << "ref(";
         _cName->print(os);
         return os<< ")";
      }
      SEM::Type* semType(SEM::Env& env);
   };

   class TypeArray : public Type {
      Type* _ty;
   public:
      TypeArray(Type* t) : _ty(t) {}
      ostream& print(ostream& os) const { 
         os << "array(";
         _ty->print(os);
         return os<< ")";
      }
      SEM::Type* semType(SEM::Env& env);
   };      

   class StmtExpr : public Stmt {
      Expr* _expr;
   public:
      StmtExpr(Expr* e) : _expr(e) {}
      ostream& print(ostream& os) const { 
         _expr->print(os);
         return os << ';' << endl;
      }      
      void semPass3(SEM::Env& env);    
      void generate(IR::Code& code);  
   };
   
   class StmtLocalDecl : public Stmt {
      Type*       _type;
      Identifier*   _id;
      SEM::LocalDescriptor* _desc;
   public:
      StmtLocalDecl(Type* t,Identifier* id) : _type(t),_id(id),_desc(0) {}
      ostream& print(ostream& os) const;
      void semPass3(SEM::Env& env);      
      void generate(IR::Code& code);
   };

   class StmtAssign : public Stmt {
      Expr* _lv;
      Expr* _expr;
   public:
      StmtAssign(Expr* l,Expr* e) : _lv(l),_expr(e) {}
      ostream& print(ostream& os) const { 
         _lv->print(os);
         os << " = ";
         _expr->print(os);
         return os << ';' << endl;
      }
      void semPass3(SEM::Env& env);      
      void generate(IR::Code& code);
   };

   class Block : public Stmt {
      std::list<AST::Stmt*> _body;
   public:
      Block(std::list<AST::Stmt*>* sList) : _body(*sList) {
         delete sList;
      }
      ostream& print(ostream& os) const { 
         os << '{';
         for(std::list<AST::Stmt*>::const_iterator it = _body.begin();
             it != _body.end(); ++it) {
            (*it)->print(os);
         }
         return os << '}' << endl;
      }  
      void semPass3(SEM::Env& env);      
      void generate(IR::Code& code);
   };

   class While : public Stmt {
      Expr* _cond;
      Stmt* _body;
   public:
      While(Expr* e,Stmt* b) : _cond(e),_body(b) {}
      ostream& print(ostream& os) const { 
         os << "while (";
         _cond->print(os);
         os << ")";
         _body->print(os);
         return os << endl;
      }      
      void semPass3(SEM::Env& env);      
      void generate(IR::Code& code);
   };

   class IfTE : public Stmt {
      Expr* _cond;
      Stmt* _tb;
      Stmt* _eb;
   public:
      IfTE(Expr* cond,Stmt* tBlock,Stmt* eBlock) 
         : _cond(cond),_tb(tBlock),_eb(eBlock) {}
      ~IfTE() {}
      ostream& print(ostream& os) const;
      void semPass3(SEM::Env& env);      
      //llvm::Value* genExpr(IR::Code&);
      void generate(IR::Code& code);
   };
   
   class Return : public Stmt {
      Expr* _ret;
   public:
      Return(Expr* e) : _ret(e) {}
      ostream& print(ostream& os) const {
         os << "return ";
         _ret->print(os);
         return os << ';' << endl;
      }
      void semPass3(SEM::Env& env);      
      void generate(IR::Code& code);
   };

   class Formal : public Decl {
      Type* _type;
      std::string _id;
      SEM::FormalDescriptor* _desc;
   public:
      Formal(Type* ty,char* id) : _type(ty),_id(id),_desc(0) { free(id);}
      ostream& print(ostream& os) const {
         _type->print(os);
         return os << " " << _id;         
      }      
      void semFormalMethod(SEM::MethodDescriptor* m,SEM::Env& env);
      void bindTo(llvm::Value* v);
   };

   class Attribute : public Decl {
      Type*     _type;
      std::string _id;
   public:
      Attribute(Type* ty,char* id) : _type(ty),_id(id) { free(id);}
      ostream& print(ostream& os) const {
         _type->print(os);
         return os << " " << _id << ';' << endl;         
      }            
      void semPass2(SEM::Env& env);      
   };
   
   class Method : public Decl {
      Type*                 _rt;
      std::string           _id;
      std::list<Decl*> _formals;
      Stmt*               _body;
      SEM::Scope*        _scope;
      SEM::Type*          _rtty; // computed return type
      SEM::MethodDescriptor* _me; // descriptor for myself.
   public:
      Method(Type* t,char* id,std::list<Decl*>* f,Stmt* body) 
         : _rt(t),_id(id),_formals(*f),_body(body) {
         free(id);
         delete f;
         _scope = 0;
         _rtty = 0;
         _me = 0;
      }
      ostream& print(ostream& os) const {
         _rt->print(os);
         os << " " << _id << '(';
         std::list<Decl*>::const_iterator it = _formals.begin();
         while (it != _formals.end()) {
            (*it)->print(os);
            ++it;
            if (it != _formals.end())
               os << ',';
         }
         os << ')' << endl;
         _body->print(os);
         return os << endl;
      }
      void semPass2(SEM::Env& env);      
      void semPass3(SEM::Env& env);      
      llvm::Function* generateMethod(IR::Code& code,SEM::ClassDescriptor* cd);
   };

   class Constructor : public Decl {
      std::string           _id;
      std::list<Decl*> _formals;
      Stmt*               _body;
      SEM::Scope*        _scope;
      SEM::MethodDescriptor* _me;
   public:
      Constructor(char* id,std::list<Decl*>* f,Stmt* body) 
         : _id(id),_formals(*f),_body(body) {
         free(id);
         delete f;
         _scope = 0;
      }
      ostream& print(ostream& os) const {
         os << _id << '(';
         for(std::list<Decl*>::const_iterator it = _formals.begin();
             it != _formals.end();++it) {
            (*it)->print(os);
            os << ',';
         }
         os << ')' << endl;
         _body->print(os);
         return os << endl;
      }
      void semPass2(SEM::Env& env);      
      void semPass3(SEM::Env& env);       
      llvm::Function* generateMethod(IR::Code& code,SEM::ClassDescriptor* cd);
   };

   class BClass : public Class {
   protected:
      std::string         _id;
      std::list<Decl*> _decls;
      SEM::Scope*      _scope;
      SEM::TypeClass*    _tty;
      SEM::ClassDescriptor* _cDesc;
   public:
      BClass(char* id,std::list<Decl*>* d) : _id(id),_decls(*d) {
         free(id);
         delete d;
         _scope = 0;
         _tty = 0;
         _cDesc = 0;
      }
      ostream& print(ostream& os) const {
         os << "class " << _id << '{' << endl;
         for(std::list<Decl*>::const_iterator it = _decls.begin();
             it != _decls.end();++it) {
            (*it)->print(os);
            os << endl;
         }
         return os << '}' << endl;
      }
      void semPass1(SEM::Env& env);
      void semPass2(SEM::Env& env);      
      void semPass3(SEM::Env& env);
      void generate(IR::Code& code);
      void emitVTBL(IR::Code& code);
   };
   
   class DClass : public BClass {
      std::string _parent;
   public:
      DClass(char* id,char* par,std::list<Decl*>* d) : BClass(id,d),_parent(par) {
         free(par);
      }
      ostream& print(ostream& os) const {
         os << "class " << _id << " extends " << _parent << '{' << endl;
         for(std::list<Decl*>::const_iterator it = _decls.begin();
             it != _decls.end();++it) {
            (*it)->print(os);
            os << endl;
         }
         return os << '}' << endl;
      }
      void semPass1(SEM::Env& env);
      void semPass2(SEM::Env& env);      
      void semPass3(SEM::Env& env);
   };

   class Program : public Decl {
      std::list<Class*>   _classes;
      SEM::ClassDescriptor*  _main;
      SEM::MethodDescriptor* _cstr;
   public:
      Program(std::list<Class*>* c) : _classes(*c) { 
         delete c;
      }
      ostream& print(ostream& os) const {
         for(std::list<Class*>::const_iterator it = _classes.begin();
             it != _classes.end();++it) {
            (*it)->print(os);
            os << endl;
         }
         return os;
      }
      void semPass1(SEM::Env& env);
      void semPass2(SEM::Env& env);      
      void semPass3(SEM::Env& env);
      void generate(IR::Code& code);
   };
};

#endif
