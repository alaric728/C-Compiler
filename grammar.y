%{
#include <math.h>
#include <stdlib.h>
#include <list>
#include "parser.H"
#include "ast.H"
#include <string.h>
#define YYERROR_VERBOSE
%}

%union {
   int        val;
   char*      id;
   AST::Node* node;
   AST::Class* cls;
   AST::Expr* expr;
   AST::Type* type;
   AST::Stmt* stmt;
   AST::Decl* decl;
   std::list<AST::Class*>* clist;
   std::list<AST::Decl*>*  dlist;
   std::list<AST::Expr*>*  elist;
   std::list<AST::Stmt*>*  slist;
}

%code{
   int yyerror(Parser* p,const char* s);
   int yylex(YYSTYPE*);
}

%defines
%pure-parser
%parse-param { Parser* parser }
%expect 1  // we can deal with 1 shift-reduce (dangling else)

%token <val> NUMBER TRUE FALSE 
%token <id>  TID THIS
%token <smb> TIF TELSE TEQ NEQ TAND TOR TNEW  TINT TBOOL TVOID TDB
%token <sbm> TRETURN TWHILE TCLASS TEXTENDS 

%type<stmt>   Statement
%type<slist>  StatementList
%type<cls>    ClassDecl
%type<clist>  ClassList
%type<expr>   Expr LValue Relation
%type<type>   BasicType Type
%type<elist>  Actuals OneOrMoreActuals
%type<dlist>  DeclList
%type<decl>   Decl
%type<dlist>  Formals OneOrMoreFormals
%type<decl>   Formal

%left TOR 
%left TAND
%left '<' '>'  LEQ GEQ
%left TEQ NEQ
%left '+' '-'
%left '*' '/'
%left '!'
%left '('
%left '['
%left '.'

%%

Top: ClassList { parser->saveRoot(new AST::Program($1));}
;

ClassList: ClassDecl ClassList { if ($1) $2->push_front($1);$$= $2; }
      |                        { $$ = new std::list<AST::Class*>();}
;

ClassDecl: TCLASS TID '{' DeclList '}' ';'      { $$ = new AST::BClass($2,$4);}
| TCLASS TID TEXTENDS TID '{' DeclList '}' ';'  { $$ = new AST::DClass($2,$4,$6);}
;

DeclList : Decl DeclList   { $$ = $2;$$->push_front($1);}
|                          { $$ = new std::list<AST::Decl*>();}
;

Decl : Type TID ';'                                { $$ = new AST::Attribute($1,$2);} 
|  Type TID '(' Formals ')' '{' StatementList '}'  { $$ = new AST::Method($1,$2,$4,new AST::Block($7));}
|       TID '(' Formals ')' '{' StatementList '}'  { $$ = new AST::Constructor($1,$3,new AST::Block($6));}
;

Formals: OneOrMoreFormals  { $$ = $1;}
|  { $$ = new std::list<AST::Decl*>();}
;

OneOrMoreFormals: Formal  { $$ = new std::list<AST::Decl*>();$$->push_front($1);}
|  Formal ',' OneOrMoreFormals  { $$ = $3;$$->push_front($1);}
;

Formal: Type TID  { $$ = new AST::Formal($1,$2);}
;

StatementList: Statement StatementList  { $$ = $2;if ($1) $2->push_front($1);}
|  { $$ = new std::list<AST::Stmt*>();}
;

Statement: Expr ';'        { $$ = new AST::StmtExpr($1);}
| Type TID ';'             { $$ = new AST::StmtLocalDecl($1,new AST::Identifier($2));}
| LValue '=' Relation ';'  { $$ = new AST::StmtAssign($1,$3);}
| '{' StatementList '}'    { $$ = new AST::Block($2);}
| TWHILE '(' Relation ')' Statement            { $$ = new AST::While($3,$5);}
| TIF '(' Relation ')' Statement                 { $$ = new AST::IfTE($3,$5,0);}
| TIF '(' Relation ')' Statement TELSE Statement { $$ = new AST::IfTE($3,$5,$7);}
| TRETURN Relation ';'                         { $$ = new AST::Return($2);}
| ';'                                          { $$ = 0;}
;

Relation: Relation TAND Relation   { $$ = new AST::And($1,$3);}
  | Relation TOR Relation          { $$ = new AST::Or($1,$3);}
  | '!' Relation                   { $$ = new AST::Not($2);} 
  | Expr '<' Expr                  { $$ = new AST::LThen($1,$3);}
  | Expr '>' Expr                  { $$ = new AST::GThen($1,$3);}
  | Expr LEQ Expr                  { $$ = new AST::LEThen($1,$3);}
  | Expr GEQ Expr                  { $$ = new AST::GEThen($1,$3);}
  | Expr TEQ Expr                  { $$ = new AST::Equal($1,$3);}
  | Expr NEQ Expr                  { $$ = new AST::NEqual($1,$3);}
  | Expr                           { $$ = $1;}
;

Expr: Expr '+' Expr   { $$ = new AST::Add($1,$3);}
| Expr '-' Expr       { $$ = new AST::Sub($1,$3);}
| Expr '*' Expr       { $$ = new AST::Mul($1,$3);}
| Expr '/' Expr       { $$ = new AST::Div($1,$3);}
| NUMBER              { $$ = new AST::Number($1);}
| TRUE                { $$ = new AST::Boolean(1);}
| FALSE               { $$ = new AST::Boolean(0);}
| '-' Expr            { $$ = new AST::Opposite($2);}
| LValue              { $$ = $1;}
| TNEW TID '(' Actuals  ')'  { $$ = new AST::InstantiateObject(new AST::Identifier($2),$4);}
| TNEW Type '[' Expr  ']'    { $$ = new AST::InstantiateArray($2,$4);}
| '(' Relation ')'           { $$ = $2;}
;

LValue: TID                       { $$ = new AST::Identifier($1);}
| LValue '(' Actuals ')'          { $$ = new AST::MthCall($1,$3);}
| LValue '.' TID                  { $$ = new AST::Deref($1,$3);}
| LValue '[' Expr ']'             { $$ = new AST::ArrayIndex($1,$3);}
| THIS                            { $$ = new AST::Identifier(strdup("this"));}
;

Actuals: OneOrMoreActuals        { $$ = $1;}
|                                { $$ = new std::list<AST::Expr*>();}
;

OneOrMoreActuals: Relation       { $$ = new std::list<AST::Expr*>();$$->push_front($1);}
| Relation ',' OneOrMoreActuals  { $$ = $3;$$->push_front($1);}
;

BasicType: TINT  { $$ = new AST::TypeInt();}
| TBOOL          { $$ = new AST::TypeBool();}
| TVOID          { $$ = new AST::TypeVoid();}
| TID            { $$ = new AST::TypeClass(new AST::Identifier($1));}
;

Type: BasicType  { $$ = $1;}
| BasicType TDB  { $$ = new AST::TypeArray($1);}
;

%%
