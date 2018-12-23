#include "sem.H"
#include "ast.H"
#include <sstream>

   void printMe(SEM::Type* t)
   {
      t->print(std::cout);
      std::cout << std::flush << std::endl;
   }

namespace SEM {


   SEM::Descriptor* TypeClass::getSymbol(const std::string&  key) 
   {
      return _scope->getSymbol(key);
   }
   
   bool TypeMethod::isEqual(Type* t) const { 
      if (t->isMethod()) {
         TypeMethod* t2 = dynamic_cast<TypeMethod*>(t);
         if (this == t2) return true;
         else {
            if (_receiver->isEqual(t2->_receiver)) {
               unsigned s1 = _fTypes.size();
               unsigned s2 = t2->_fTypes.size();
               if (s1 == s2)  {
                  for(int k=0;k<s1;k++) {
                     bool eq = _fTypes[k]->isEqual(t2->_fTypes[k]);
                     if (!eq) return false;
                  }
                  return true;
               } else return false;
            } else return false;
         }
      } else return false;            
   }
   
   bool TypeMethod::canOverride(TypeMethod* t) {
      if (t->_receiver->isSuperOf(_receiver)) {
         bool rteq = _rt->isEqual(t->_rt);
         unsigned s1 = _fTypes.size();
         unsigned s2 = t->_fTypes.size();
         if (rteq && s1 == s2) {
            for(unsigned k=1;k<s1;k++) {
               bool eq = _fTypes[k]->isEqual(t->_fTypes[k]);
               if (!eq) return false;
            }
            return true;
         } else return false;
      } else return false;
   }
   
   bool TypeClass::isEqual(Type* t) const { 
      if (t->isClass()) {
         TypeClass* t2 = dynamic_cast<TypeClass*>(t);
         if (this == t2) return true;
         else {
            if (_name == t2->_name) return true;
            else return false;
         }
      } else return false;
   }

   bool TypeClass::hasMethod(string name,TypeMethod* mty)
   {
      SEM::Descriptor* md = getSymbol(name);
      if (md!=0 && md->getType()->isMethod()) {
         TypeMethod* emt = dynamic_cast<TypeMethod*>(md->getType());
         if (mty->canOverride(emt)) 
            return true;
      }
      if (_parent)
         return _parent->hasMethod(name,mty);
      else return false;
   }

   MethodDescriptor* TypeClass::getMethod(string name,TypeMethod* mty)
   {
      SEM::Descriptor* md = getSymbol(name);
      if (md!=0 && md->getType()->isMethod()) {
         TypeMethod* emt = dynamic_cast<TypeMethod*>(md->getType());
         if (mty->canOverride(emt)) 
            return dynamic_cast<MethodDescriptor*>(md);
      } 
      if (_parent)
         return _parent->getMethod(name,mty);
      else return 0;      
   }


   std::ostream&  TypeClass::print(ostream& os) const { 
      os << "class(" << _name << ")";
      if (_parent) os << " : " << *_parent;
      if (_scope) os << *_scope << endl;         
      return os;
   }

   bool TypeClass::isSuperOf(TypeClass* t2)
   {
      if (this == t2) 
         return true;
      else if (_name == t2->_name)
         return true;
      else if (t2->_parent)
         return isSuperOf(t2->_parent);
      else return false;
   }
   
   Type* TypeMethod::acceptCall(std::vector<SEM::Type*>& aty)
   {
      if (aty.size() == _fTypes.size()) {
         for(int k=0;k<aty.size();k++) {
            bool ok = _fTypes[k]->accept(aty[k]);
            if (!ok) return 0;
         }
         return _rt;
      } else return 0;
   }

   int Scope::scanMethods(int lastM,TypeClass* toCheck)
   {
      // Scan the scope of a class (whose direct ancestor is toCheck)
      // to "number" the methods. Check if the method is overriding something
      // In the parent class. If that's the case, reuse the number of the overriden 
      // method. If not, keep numbering sequentially from lastM. 
      for(std::map<std::string,Descriptor*>::iterator i=_map.begin();i!=_map.end();++i) {
         Descriptor* d = i->second;
         if (d->isMethod()) {
            MethodDescriptor* md = dynamic_cast<MethodDescriptor*>(d);
            TypeMethod* tm = dynamic_cast<TypeMethod*>(md->getType());
            if (toCheck && toCheck->hasMethod(i->first,tm)) {
               MethodDescriptor* overriden = toCheck->getMethod(i->first, tm);
               md->setOffset(overriden->getOffset());
            } else md->setOffset(lastM++);
         }
      }
      return lastM;
   }

   Descriptor* Scope::addSymbol(std::string key,Descriptor* d) 
   {
      //assert(_map.find() == 0);
      _map[key] = d;
      return d;
   }
   Descriptor* Scope::getSymbol(std::string key,bool rec) 
   {
      if (_map.count(key) > 0)
         return _map[key];
      else if (rec && _parent) 
         return _parent->getSymbol(key,rec);
      else return 0;
   }

   Env::Env()
   {
      _tint   = new TypeInt();
      _tbool  = new TypeBool();
      _tvoid  = new TypeVoid();
      _terror = new TypeError();
      _env.push(new Scope());
   }

   Env::~Env()
   {}

   Scope* Env::openScope()
   {
      Scope* s = new Scope(_env.top());
      _env.push(s);
      return s;
   }

   void Env::pushScope(Scope* s)
   {
      _env.push(s);
   }

   Scope* Env::popScope()
   {
      Scope* rv = _env.top();
      _env.pop();
      return rv;
   }

   Descriptor* Env::addSymbol(std::string key,Descriptor* d)
   {
      return _env.top()->addSymbol(key,d);
   }

   Descriptor* Env::addMethod(std::string key,MethodDescriptor* d)
   {
      addSymbol(key,d);
      return d;
   }

   Descriptor* Env::getSymbol(std::string key,bool rec)
   {
      return _env.top()->getSymbol(key,rec);
   }

   void Env::reportError(std::string s)
   {
      cerr << "semantic error:" << s << endl;
      throw -1;
   }

   void Env::analyze(AST::Node* root)
   {
      root->semPass1(*this);
      root->semPass2(*this);
      root->semPass3(*this);
      //cout << * _env.top() << endl;
   }

   void MethodDescriptor::addFormal(std::string key,FormalDescriptor* fd)
   {
      dynamic_cast<TypeMethod*>(_type)->addFormal(key,fd->getType());
      _args.push_back(fd);
   }
   
   // This is numbering all the methods in the class. 
   // It should start by numbering the methods in the parent class. 
   // Then carry on in this class.
   int  ClassDescriptor::labelMethods() 
   {
      if (_nbM==-1) {
         int nbP = _pClass ? _pClass->labelMethods() : 0;
         TypeClass* me = dynamic_cast<TypeClass*>(getType());
         Scope* cc = me->getScope();
         nbP = cc->scanMethods(nbP,me->getParent()); // scan methods for overrides. Label.
         return _nbM = nbP; // save the number of methods in the class. 
      } else return _nbM;   // return what was previously computed. 
   }
}

namespace AST {
   using namespace SEM;
   using namespace std;

   void Program::semPass1(Env& env) {
      for(std::list<Class*>::iterator i = _classes.begin();i!=_classes.end();++i) 
         (*i)->semPass1(env);      
   }

   void BClass::semPass1(Env& env) 
   {
      Descriptor* d = env.getSymbol(_id);
      if (d==0) {
         _tty = new SEM::TypeClass(_id,0);
         env.addSymbol(_id,_cDesc = new ClassDescriptor(_tty));
     } else {
         ostringstream oss;
         oss << "The name " << _id << " is already used to define a type " << *d->getType() << ends;
         env.reportError(oss.str());
      }
   }

   void DClass::semPass1(Env& env) 
   {
      Descriptor* d = env.getSymbol(_parent);
      SEM::Type* pC = d ? d->getType() : 0;
      
      ostringstream oss;
      if (pC==0) {
         oss << "Parent class " << _parent << " is undefined" << ends;
         env.reportError(oss.str());
      }
      if (dynamic_cast<SEM::TypeClass*>(pC)==0) {
         oss << "Name " << _parent << " is not a class. " << *pC << ends;
         env.reportError(oss.str());
      }
      _tty = new SEM::TypeClass(_id,dynamic_cast<SEM::TypeClass*>(pC));
      env.addSymbol(_id,_cDesc = new ClassDescriptor(_tty,dynamic_cast<ClassDescriptor*>(d)));      
   }


   void Program::semPass2(SEM::Env& env) {
      for(std::list<Class*>::iterator i = _classes.begin();i!=_classes.end();++i) 
         (*i)->semPass2(env);      
   }
   void Program::semPass3(SEM::Env& env) {
      for(std::list<Class*>::iterator i = _classes.begin();i!=_classes.end();++i) 
         (*i)->semPass3(env);      
      Descriptor* mDesc = env.getSymbol("Main"); // look for a main class.
      if (mDesc==0) {
         ostringstream oss;
         oss << "There is no 'Main' class to instantiate!" << ends;
         env.reportError(oss.str());
      }
      if (!mDesc->getType()->isClass()) {
         ostringstream oss;
         oss << "The object named 'Main' is not class but a [" 
             << *mDesc->getType() << ']'
             << ends;
         env.reportError(oss.str());         
      }      
      _main = dynamic_cast<SEM::ClassDescriptor*>(mDesc);
      SEM::TypeClass* tc = dynamic_cast<SEM::TypeClass*>(_main->getType());
      SEM::Descriptor* cstr = tc->getSymbol("Main"); // looking for constructor
      if (cstr==0 || !cstr->getType()->isMethod()) {
         ostringstream oss;
         oss << "The class named 'Main' does not have a constructor" << ends;
         env.reportError(oss.str());         
      }
      TypeMethod* cty = dynamic_cast<TypeMethod*>(cstr->getType());
      if (cty->nbExpectedArgs()!=1) {
         ostringstream oss;
         oss << "The class constructor does not take the expected # of arguments." << ends;
         env.reportError(oss.str());         
      }
      _cstr = dynamic_cast<MethodDescriptor*>(cstr);
   }

   void BClass::semPass2(SEM::Env& env) {
      Scope* cs = env.openScope();
      _tty->setScope(cs);
      env.setCurrentClass(_tty,_cDesc);
      for(std::list<Decl*>::iterator i = _decls.begin();i != _decls.end();++i) 
         (*i)->semPass2(env);      
      env.popScope();
      _scope = cs;
   }

   void DClass::semPass2(SEM::Env& env) {
      Scope* cs = env.openScope();      
      _tty->setScope(cs);
      env.setCurrentClass(_tty,_cDesc);
      for(std::list<Decl*>::iterator i = _decls.begin();i != _decls.end();++i) 
         (*i)->semPass2(env);      
      env.popScope();
      _scope = cs;      
   }

   void BClass::semPass3(SEM::Env& env) {
      _cDesc->labelMethods(); // now that all the methods are known, label them!
      env.pushScope(_scope);
      for(std::list<Decl*>::iterator i = _decls.begin();i != _decls.end();++i) {
         (*i)->semPass3(env);
      }      
      env.popScope();
   }

   void DClass::semPass3(SEM::Env& env) {
      _cDesc->labelMethods(); // now that all the methods are known, label them!
      env.pushScope(_scope);
      for(std::list<Decl*>::iterator i = _decls.begin();i != _decls.end();++i) {
         (*i)->semPass3(env);
      }      
      env.popScope();
   }

   void Attribute::semPass2(SEM::Env& env)
   {
      Descriptor* idDesc = env.getSymbol(_id);
      if (idDesc) {
         ostringstream oss;
         oss << _id << " already defined" << ends;
         env.reportError(oss.str());
      }
      SEM::Type* ty = _type->semType(env);
      env.addSymbol(_id,new FieldDescriptor(ty));
   }

   void Method::semPass2(SEM::Env& env)
   {
      SEM::Type* rtty = _rt->semType(env);
      Descriptor* idDesc = env.getSymbol(_id);
      if (idDesc!=0) {
         ostringstream oss;
         oss << _id << " already defined in this class" << endl;
         env.reportError(oss.str());
      }
      TypeMethod* tm = new TypeMethod(env.getCurrentClass(),rtty);
      FormalDescriptor* rec = new FormalDescriptor(new SEM::TypeInstance(env.getCurrentClass()));
      _me = new MethodDescriptor(env.getCurrentClassDesc(),rec,tm);
      _me->addFormal("this",rec);
      
      std::list<Decl*>::iterator it = _formals.begin();
      Scope* fScope = env.openScope();      
      while (it != _formals.end()) {
         (*it)->semFormalMethod(_me,env);
         ++it;
      }
      env.addSymbol("this",rec);
      env.popScope();
      env.addMethod(_id,_me);
      _scope = fScope;
      _rtty = rtty;
   }

   void Method::semPass3(SEM::Env& env) 
   {
      env.pushScope(_scope);
      env.setReturnType(_rtty);
      _body->semPass3(env);
      env.popScope();
   }

   void Constructor::semPass2(SEM::Env& env)
   {
      Descriptor* idDesc = env.getSymbol(_id);
      if (idDesc!=0) {
         ostringstream oss;
         oss << _id << " already defined in this class" << endl;
         env.reportError(oss.str());
      }
      TypeMethod* tm = new TypeMethod(env.getCurrentClass(),env.getTypeVoid());
      FormalDescriptor* rec=new FormalDescriptor(new SEM::TypeInstance(env.getCurrentClass()));
      _me = new MethodDescriptor(env.getCurrentClassDesc(),rec,tm);
      _me->addFormal("this",rec);

      std::list<Decl*>::iterator it = _formals.begin();
      Scope* fScope = env.openScope();
      while (it != _formals.end()) {
         (*it)->semFormalMethod(_me,env);
         ++it;
      }
      env.addSymbol("this", rec);
      env.popScope();
      env.addMethod(_id,_me);
      _scope = fScope;
   }

   void Constructor::semPass3(SEM::Env& env) 
   {
      env.pushScope(_scope);
      env.openScope();
      env.setReturnType(0);
      _body->semPass3(env);
      env.popScope();
      env.popScope();
   }

   void Formal::semFormalMethod(SEM::MethodDescriptor* m,SEM::Env& env)
   {
      SEM::Type* rtty = _type->semType(env);
      Descriptor* lDesc = env.getSymbol(_id);
      if (lDesc) {
         ostringstream oss;
         oss << "formal " << _id << " already defined as " << *lDesc->getType() << ends;
         env.reportError(oss.str());
      }
      env.addSymbol(_id,_desc = new FormalDescriptor(rtty));
      m->addFormal(_id,_desc);
   }

   SEM::Type* TypeInt::semType(SEM::Env& env)
   {
      return env.getTypeInt();
   }

   SEM::Type* TypeBool::semType(SEM::Env& env)
   {
      return env.getTypeBool();
   }

   SEM::Type* TypeVoid::semType(SEM::Env& env)
   {
      return env.getTypeVoid();
   }

   SEM::Type* TypeClass::semType(SEM::Env& env)
   {
      Descriptor* idDesc = env.getSymbol(_cName->get(),true); // recursive
      if (idDesc==0) {
         ostringstream oss;
         oss << "class " << _cName->get() << " not found" << ends;
         env.reportError(oss.str());
      }
      SEM::TypeClass* tc = dynamic_cast<SEM::TypeClass*>(idDesc->getType());
      if (tc==0) {
         ostringstream oss;
         oss << "type " << *(idDesc->getType()) << " is not a class type" << endl;
         env.reportError(oss.str());
      }
      return new SEM::TypeInstance(tc);
   }
   
   SEM::Type* TypeArray::semType(SEM::Env& env)
   {
      SEM::Type* elty = _ty->semType(env);      
      return new SEM::TypeArray(elty);
   }
   
   void Block::semPass3(SEM::Env& env)
   {
      env.openScope();
      for(std::list<AST::Stmt*>::iterator it = _body.begin();it!=_body.end();++it) 
         (*it)->semPass3(env);      
      env.popScope();
   }

   void StmtLocalDecl::semPass3(SEM::Env& env)
   {
      SEM::Type* lty = _type->semType(env);
      SEM::Descriptor* lDesc = env.getSymbol(_id->get(),false);//non-rec lookup
      if (lDesc) {
         ostringstream oss;
         oss << _id->get() << " already defined in this block" << endl;
      } 
      env.addSymbol(_id->get(),_desc = new LocalDescriptor(lty));
   }

   void StmtAssign::semPass3(SEM::Env& env)
   {
      SEM::Type* lvty = _lv->semType(env);
      SEM::Type* exty = _expr->semType(env);
      if (!lvty->accept(exty)) {
         ostringstream oss;
         oss << "the lvalue of type " << *lvty << " does not accept a value of type " << exty << endl;
         env.reportError(oss.str());
      }      
   }

   void IfTE::semPass3(SEM::Env& env)
   {
      SEM::Type* cty = _cond->semType(env);
      if (cty->isBool()) {
         _tb->semPass3(env);
         if (_eb)
            _eb->semPass3(env);
      } else {
         ostringstream oss;
         oss << "Expecting a boolean in if-then-else. Got " << *cty << endl;
         env.reportError(oss.str());         
      }
   }

   void While::semPass3(SEM::Env& env) 
   {
      SEM::Type* cty = _cond->semType(env);
      if (cty->isBool()) {
         _body->semPass3(env);
      } else {
         ostringstream oss;
         oss << "Expecting a boolean in while. Got " << *cty << endl;
         env.reportError(oss.str());         
      }
   }

   void StmtExpr::semPass3(SEM::Env& env)
   {
      _expr->semType(env);
   }

   void Return::semPass3(SEM::Env& env) 
   {
      SEM::Type* rty = _ret->semType(env);
      SEM::Type* ety = env.getReturnType();
      if (ety==0) {
         ostringstream oss;
         oss << "Wasn't expecting a return in this method." << endl;
         env.reportError(oss.str());
      }
      if (!ety->accept(rty)) {
         ostringstream oss;
         oss << "Returned type " << *rty << " does not match expected return: " << *ety << endl;
         env.reportError(oss.str());
      }
   }

   
   SEM::Type* Number::semType(SEM::Env& env)
   {
      return _theType = env.getTypeInt();
   }

   SEM::Type* Boolean::semType(SEM::Env& env)
   {
      return _theType = env.getTypeBool();
   }

   SEM::Type* Identifier::semType(SEM::Env& env) 
   {
      SEM::Descriptor* vDesc = env.getSymbol(_value,true);
      if (!vDesc) {
         ostringstream oss;
         oss << _value << " is undefined" << ends;
         env.reportError(oss.str());
      }
      if (vDesc->isField()) {
         SEM::Descriptor* oDesc = env.getSymbol("this",true);
         if (oDesc->getType()->isInstance()) {
            _oDesc = oDesc;
         } else {
            ostringstream oss;
            oss << "Expecting 'this' to denote a class instance in field lookup. Got " << *oDesc << ends;
            env.reportError(oss.str());            
            return 0;
         }
      }
      _desc = vDesc;      
      return _theType = _desc->getType();      
   }

   SEM::Type* MthCall::semType(SEM::Env& env)
   {
      _rcv = _callee->getReceiver();
      SEM::Type* calty = _callee->semType(env);      
      if (calty->isMethod()) {
         SEM::Type* rcvty = _rcv->semType(env);
         SEM::TypeMethod* mth = dynamic_cast<SEM::TypeMethod*>(calty);
         std::list<Expr*>::iterator it = _args.begin();
         std::vector<SEM::Type*> aty;
         aty.push_back(rcvty);
         while (it != _args.end()) {
            aty.push_back((*it)->semType(env));
            ++it;
         }
         SEM::Type* rt = mth->acceptCall(aty);
         if (rt)
            return _theType = rt;
         else {
            ostringstream oss;
            oss << "The method " << *mth << " does not accept arguments of type ";
            std::vector<SEM::Type*>::iterator i = aty.begin();
            while(i != aty.end()) {
               oss << *i;
               ++i;
               if (i != aty.end())
                  oss << ',';
            }
            oss << ends;
            env.reportError(oss.str());
         }
      } else {
         ostringstream oss;
         oss << "this is not a method. The callee has type:" << *calty << ends;
         env.reportError(oss.str());
      }
      return 0;
   }
   
   SEM::Type* InstantiateObject::semType(SEM::Env& env)
   {
      SEM::Descriptor* sd = env.getSymbol(_class->get(),true);
      if (sd==0) {
         ostringstream oss;
         oss << "class " << _class->get() << " not found" << ends;
         env.reportError(oss.str());
      }
      SEM::TypeClass* tc = dynamic_cast<SEM::TypeClass*>(sd->getType());
      if (tc==0) {
         ostringstream oss;
         oss << "type " << *(sd->getType()) << " is not a class type" << endl;
         env.reportError(oss.str());
      }
      SEM::Descriptor* md = tc->getSymbol(_class->get());
      SEM::Type* rcty = new SEM::TypeInstance(tc); // receiver type
      if (md->getType()->isMethod()) {
         SEM::TypeMethod* mth = dynamic_cast<SEM::TypeMethod*>(md->getType());
         std::list<Expr*>::iterator it = _args.begin();
         std::vector<SEM::Type*> aty;
         aty.push_back(rcty);
         while (it != _args.end()) {
            aty.push_back((*it)->semType(env));
            ++it;
         }
         SEM::Type* rt = mth->acceptCall(aty);
         if (rt==0) {
            ostringstream oss;
            oss << "The constructor " << *mth << " does not accept arguments of type ";
            std::vector<SEM::Type*>::iterator i = aty.begin();
            while(i != aty.end()) {
               oss << *i;
               ++i;
               if (i != aty.end())
                  oss << ',';
            }
            oss << ends;
            env.reportError(oss.str());            
         }
      } else {
         ostringstream oss;
         oss << "The name " << _class->get() << " does not refer to a constructor" << endl;
         env.reportError(oss.str());
      
      }
      _desc  = dynamic_cast<ClassDescriptor*>(sd);
      _mdesc = dynamic_cast<MethodDescriptor*>(md);
      return _theType = rcty;
   }

   SEM::Type* InstantiateArray::semType(SEM::Env& env)
   {
      SEM::Type* et = _type->semType(env);
      if (et == 0) {
         ostringstream oss;
         oss << "The expression does not denote a type" << endl;
         env.reportError(oss.str());
      }
      SEM::Type* st = _args->semType(env);
      if (!st->isInt()) {
         ostringstream oss;
         oss << "The size should be an integer" << endl;
         env.reportError(oss.str());
      }
      return _theType = _at = new SEM::TypeArray(et);
   }

   
   SEM::Type* Binary::semType(SEM::Env& env)
   {
      SEM::Type* lty = _left->semType(env);
      SEM::Type* rty = _right->semType(env);
      if (lty == rty)
         return _theType = lty;
      else {
         ostringstream oss;
         oss << *lty << " and " << *rty << " are incompatible for " << opName() << ends;
         env.reportError(oss.str());
         return 0;
      }
   }

   SEM::Type* Relational::semType(SEM::Env& env)
   {
      SEM::Type* lty = _left->semType(env);
      SEM::Type* rty = _right->semType(env);
      if (lty == rty)
         return _theType = env.getTypeBool();
      else {
         ostringstream oss;
         oss << *lty << " and " << *rty << " are incompatible for " << opName() << ends;
         env.reportError(oss.str());
         return 0;
      }      
   }

   SEM::Type* And::semType(SEM::Env& env)
   {
      SEM::Type* lty = _left->semType(env);
      SEM::Type* rty = _right->semType(env);
      if (lty == rty) {
         if (lty->isBool())
            return _theType = env.getTypeBool();
         else {
            ostringstream oss;
            oss << *lty << " and " << *rty << " must be booleans for " << opName() << ends;
            env.reportError(oss.str());
            return 0;            
         }
      } else {
         ostringstream oss;
         oss << *lty << " and " << *rty << " are incompatible for " << opName() << ends;
         env.reportError(oss.str());
         return 0;
      }     
   }

   SEM::Type* Or::semType(SEM::Env& env)
   {
      SEM::Type* lty = _left->semType(env);
      SEM::Type* rty = _right->semType(env);
      if (lty == rty) {
         if (lty->isBool())
            return _theType = env.getTypeBool();
         else {
            ostringstream oss;
            oss << *lty << " and " << *rty << " must be booleans for " << opName() << ends;
            env.reportError(oss.str());
            return 0;            
         }
      } else {
         ostringstream oss;
         oss << *lty << " and " << *rty << " are incompatible for " << opName() << ends;
         env.reportError(oss.str());
         return 0;
      }     
   }

   SEM::Type* Opposite::semType(SEM::Env& env)
   {
      SEM::Type* oty = _op->semType(env);
      if (oty->isInt()) {
         return _theType = oty;
      } else {
         ostringstream oss;
         oss << "unary - only applies to integers. Got " << *oty << ends;
         env.reportError(oss.str());
         return 0;
      }
   }

   SEM::Type* Not::semType(SEM::Env& env)
   {
      SEM::Type* oty = _op->semType(env);
      if (oty->isBool()) {
         return _theType = oty;
      } else {
         ostringstream oss;
         oss << "Boolean negation (!) only applies to booleans. Got " << *oty << ends;
         env.reportError(oss.str());
         return 0;
      }
   }

   SEM::Type* Deref::semType(SEM::Env& env)
   {
      SEM::Type* oty = _obj->semType(env);
      if (oty->isInstance()) {
         SEM::TypeInstance* ity = dynamic_cast<SEM::TypeInstance*>(oty);
         _aDesc = ity->getType()->getSymbol(_name);
         SEM::Type* fty = _aDesc->getType();
         return _theType = fty;
      } else {
         ostringstream oss;
         oss << "Expecting an instance to apply the '.' operator. Got " << *oty << ends;
         env.reportError(oss.str());
         return 0;
      }
   }

   SEM::Type* ArrayIndex::semType(SEM::Env& env)
   {
      SEM::Type* at  = _array->semType(env);
      SEM::Type* idx = _index->semType(env);
      if (idx->isInt()) {
         if (at->isArray()) {
            return _theType = dynamic_cast<SEM::TypeArray*>(at)->getType();
         } else {
            ostringstream oss;
            oss << "Expecting an array in an array index. Got " << *at << ends;
            env.reportError(oss.str());
            return 0;
         }
      } else {
         ostringstream oss;
         oss << "Expecting an integer in an array index. Got " << *idx << ends;
         env.reportError(oss.str());
         return 0;
      }
   }

}
