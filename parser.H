#ifndef __PARSER_H
#define __PARSER_H

namespace AST {
   class Node;
}

class Parser {
   AST::Node* _root;
public: 
   Parser();
   ~Parser();
   void run(const char* fn = 0);
   void saveRoot(AST::Node* root) { _root = root;}
   AST::Node* getRoot() { return _root;}
};

int yyparse(Parser*);

#endif
