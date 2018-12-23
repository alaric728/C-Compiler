#include <iostream>
#include <iomanip>

#include "parser.H"
#include "sem.H"
#include "codegen.H"

using namespace std;
int main(int argc,char* argv[]) {
   const char* fn = 0;
   if (argc == 2)
      fn = argv[1];
   //cout << argc << ":input filename:" << fn << endl;
   Parser p;
   p.run(fn);
//   cout << "root:" << p.getRoot() << endl;
   AST::Node* root = p.getRoot();
   if (root) {
//      root->print(std::cout);
      try {
         SEM::Env env;
         env.analyze(root);

//         root->print(std::cout);

         IR::Code gen;
         gen.generate(root);

      } catch(int ec) {
         return ec;
      }
      /*      Code code;   
      code.generate(root);
      code.dump();
      */
   } else std::cout << "couldn't parse" << std::endl;
}
