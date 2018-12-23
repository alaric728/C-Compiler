#include "ast.H"
#include "sem.H"

using namespace std;
namespace AST {
   Node::Node()  {}
   Node::~Node() {}

   ostream& Binary::print(ostream& os) const 
   {
      _left->print(os);
      os << std::string(opName());
      return _right->print(os);
   }

   ostream& MthCall::print(ostream& os) const {
      _callee->print(os);
      os << '(';
      for(std::list<Expr*>::const_iterator i = _args.begin();i!=_args.end();++i) {
         (*i)->print(os);
         os << " ";
      }
      os << ')';
      return os;
   }

   ostream& IfTE::print(ostream& os) const
   {
      os << "if (";
      _cond->print(os);
      os << ") then ";
      _tb->print(os);
      if (_eb) {
         os << " else ";
         _eb->print(os);
      }
      return os;
   }

   ostream& StmtLocalDecl::print(ostream& os) const 
   { 
      _type->print(os);
      os << " : ";
      _id->print(os);
      if (_desc)
         os << " " << *_desc;
      return os << ';' << endl;
   }

   ostream& Identifier::print(ostream& os) const 
   {
      os << _value;
      if (_desc)
         os << " " << *_desc;
      return os;
   }
}
