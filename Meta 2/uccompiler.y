%{

#include <stddef.h>

#include "ast.h"
#include <stddef.h>

int yylex(void);
void yyerror(char *);

struct node *program;

%}


%token BITWISEAND BITWISEOR BITWISEXOR AND ASSIGN MUL COMMA DIV EQ GE GT LBRACE LE LPAR LT MINUS MOD
%token NE NOT OR PLUS RBRACE RPAR SEMI CHAR ELSE WHILE IF INT SHORT DOUBLE RETURN VOID

%token<token> CHRLIT IDENTIFIER NATURAL DECIMAL RESERVED


%type<node> FunctionsAndDeclarations FunctionDefinition FunctionBody DeclarationsAndStatements
%type<node> FunctionDeclaration FunctionDeclarator ParameterList ParameterDeclaration Declaration
%type<node> TypeSpec Declarator Statement Expr Program Aux_Declaration StatList Aux_Expr

%union{
    char *token;
    struct node *node;
}

%left LOW
%left COMMA
%right ASSIGN
%left OR
%left AND
%left BITWISEOR
%left BITWISEXOR
%left BITWISEAND
%left EQ NE
%left GT LE GE LT
%left PLUS MINUS
%left MUL DIV MOD
%right NOT
%left LPAR RPAR 

%nonassoc ELSE

%%

Program: FunctionsAndDeclarations                                           {   
                                                                                $$ = program = newnode(Program, NULL);
                                                                                addchild($$, $1); 
                                                                            }

FunctionsAndDeclarations: FunctionDefinition                                {   
                                                                                $$ = $1;
                                                                            }
                        | FunctionDeclaration                               {   
                                                                                $$ = $1;
                                                                            }
                        | Declaration                                       {   
                                                                                $$ = $1;
                                                                            }
                        | FunctionsAndDeclarations FunctionDefinition       {   
                                                                                $$ = $1;
                                                                                addchild($$, $2);

                                                                            }
                        | FunctionsAndDeclarations FunctionDeclaration      { 
                                                                                $$ = $1;    
                                                                                addchild($$, $2);
                            
                                                                            }
                        | FunctionsAndDeclarations Declaration              { 
                                                                                $$ = $1;    
                                                                                addchild($$, $2);

                                                                            }
                        ;

FunctionDefinition: TypeSpec FunctionDeclarator FunctionBody {
                                                                                $$ = newnode(FuncDefinition, NULL);
                                                                                addchild($$, $1);
                                                                                addchild($$, $2);
                                                                                addchild($$, $3);

                                                                            }
                  ;

FunctionBody: LBRACE DeclarationsAndStatements RBRACE                       {
                                                                                $$ = newnode(FuncBody, NULL);
                                                                                addchild($$, $2);
                                                                            }
            | LBRACE RBRACE                                                 {}
            ;

DeclarationsAndStatements: DeclarationsAndStatements Statement              {
                                                                                $$ = $1;
                                                                                addchild($$, $2);

                                                                            }
                         | DeclarationsAndStatements Declaration            {
                                                                                $$ = $1;
                                                                                addchild($$, $2);
                                                                            }
                         | Statement                                        {
                                                                                $$ = $1;
                                                                            }
                         | Declaration                                      {
                                                                                $$ = $1;
                                                                            }
                         ;

FunctionDeclaration: TypeSpec FunctionDeclarator SEMI                       {
                                                                                $$ = newnode(FuncDeclaration, NULL);
                                                                                addchild($$, $1);
                                                                                addchild($$, $2);
                                                                            }
                   ;

FunctionDeclarator: IDENTIFIER LPAR ParameterList RPAR                      {
                                                                                
                                                                                $$ = newnode(Identifier, $1);
                                                                                addchild($$, $3);

                                                                            }

ParameterList: ParameterDeclaration                                         { 
                                                                                $$ = newnode(ParamList, NULL);
                                                                                addchild($$, $1);
                                                                            }
             | ParameterList COMMA ParameterDeclaration                     {
                                                                                $$ = $1;
                                                                                addchild($$, $3);
                                                                            }
             ; 

ParameterDeclaration: TypeSpec                                              {
                                                                                $$ = newnode(ParamDeclaration, NULL);
                                                                                addchild($$, $1);
                                                                            }
                    | TypeSpec IDENTIFIER                                   {}
                    ;

Declaration: TypeSpec Declarator Aux_Declaration SEMI                       {
                                                                                $$ = newnode(Declaration, NULL);
                                                                                addchild($$, $1);
                                                                                addchild($$, $2);
                                                                                addchild($$, $3);
                                                                            }
           | TypeSpec Declarator SEMI                                       {}

Aux_Declaration: COMMA Declarator                                           {
                                                                                $$ = $2;
                                                                            }
               | Aux_Declaration COMMA Declarator                           {
                                                                                $$ = $1;
                                                                                addchild($$, $3);
                                                                            }
               ;

TypeSpec: CHAR                                                              {
                                                                                $$ = newnode(Char, NULL);
                                                                            }
        | INT                                                               {
                                                                                $$ = newnode(Int, NULL);
                                                                            }
        | VOID                                                              {
                                                                                $$ = newnode(Void, NULL);
                                                                            }
        | SHORT                                                             {
                                                                                $$ = newnode(Short, NULL);
                                                                            }
        | DOUBLE                                                            {
                                                                                $$ = newnode(Double, NULL);
                                                                            }
        ;

Declarator: IDENTIFIER                                                      {
                                                                                $$ = newnode(Identifier, $1);
                                                                            }
          | IDENTIFIER ASSIGN Expr                                          {
                                                                                $$ = newnode(Identifier, $1);
                                                                                addchild($$, $3);
                                                                            }
          ;

Statement: Expr SEMI                                                        { $$ = $1; }
         | SEMI                                                             {}
         | LBRACE RBRACE                                                    {}
         | LBRACE StatList RBRACE                                           { $$ = $2; }
         | IF LPAR Expr RPAR Statement                       %prec LOW      { $$ = newnode(If, NULL); addchild($$, $3); addchild($$, $5); }      
         | IF LPAR Expr RPAR Statement ELSE Statement                       { $$ = newnode(If, NULL); addchild($$, $3); addchild($$, $5); addchild($$, $7); }
         | WHILE LPAR Expr RPAR Statement                                   { $$ = newnode(While, NULL); addchild($$, $3); addchild($$, $5); }
         | RETURN SEMI                                                      { $$ = newnode(Return, NULL); }
         | RETURN Expr SEMI                                                 { $$ = newnode(Return, NULL); }
         ;

StatList: Statement                                                         { 
                                                                                $$ = newnode(StatList, NULL);
                                                                                addchild($$, $1);
                                                                            }
        | StatList Statement                                                {
                                                                                $$ = $1;
                                                                                addchild($$, $2);
                                                                            }
        ; 

Expr: Expr ASSIGN Expr                                                      {$$ = newnode(Store, NULL); addchild($$, $1); addchild($$, $3);}
    | Expr PLUS Expr                                                        {$$ = newnode(Add, NULL); addchild($$, $1); addchild($$, $3);}
    | Expr MINUS Expr                                                       {$$ = newnode(Sub, NULL); addchild($$, $1); addchild($$, $3);}
    | Expr MUL Expr                                                         {$$ = newnode(Mul, NULL); addchild($$, $1); addchild($$, $3);}
    | Expr DIV Expr                                                         {$$ = newnode(Div, NULL); addchild($$, $1); addchild($$, $3);}
    | Expr MOD Expr                                                         {$$ = newnode(Mod, NULL); addchild($$, $1); addchild($$, $3);}
    | Expr OR Expr                                                          {$$ = newnode(Or, NULL); addchild($$, $1); addchild($$, $3);}
    | Expr AND Expr                                                         {$$ = newnode(And, NULL); addchild($$, $1); addchild($$, $3);}
    | Expr BITWISEAND Expr                                                  {$$ = newnode(BitWiseAnd, NULL); addchild($$, $1); addchild($$, $3);}
    | Expr BITWISEOR Expr                                                   {$$ = newnode(BitWiseOr, NULL); addchild($$, $1); addchild($$, $3);}
    | Expr BITWISEXOR Expr                                                  {$$ = newnode(BitWiseXor, NULL); addchild($$, $1); addchild($$, $3);}
    | Expr EQ Expr                                                          {$$ = newnode(Eq, NULL); addchild($$, $1); addchild($$, $3);}
    | Expr NE Expr                                                          {$$ = newnode(Ne, NULL); addchild($$, $1); addchild($$, $3);}
    | Expr LE Expr                                                          {$$ = newnode(Le, NULL); addchild($$, $1); addchild($$, $3);}
    | Expr GE Expr                                                          {$$ = newnode(Ge, NULL); addchild($$, $1); addchild($$, $3);}
    | Expr LT Expr                                                          {$$ = newnode(Lt, NULL); addchild($$, $1); addchild($$, $3);}
    | Expr GT Expr                                                          {$$ = newnode(Gt, NULL); addchild($$, $1); addchild($$, $3);}
    | PLUS Expr                                                             {$$ = newnode(Add, NULL); addchild($$, $2);}
    | MINUS Expr                                                            {$$ = newnode(Sub, NULL); addchild($$, $2);}
    | NOT Expr                                                              {$$ = newnode(Not, NULL); addchild($$, $2);}
    | IDENTIFIER LPAR RPAR                                                  {$$ = newnode(Call, NULL); addchild($$, newnode(Identifier, $1)); addchild($$, newnode(Null, NULL));}
    | IDENTIFIER LPAR Aux_Expr RPAR                                         {$$ = newnode(Call, NULL); addchild($$, newnode(Identifier, $1)); addchild($$, $3);}
    | IDENTIFIER                                                            {$$ = newnode(Identifier, $1);}
    | NATURAL                                                               {$$ = newnode(Natural, $1);}
    | CHRLIT                                                                {$$ = newnode(ChrLit, $1);}
    | DECIMAL                                                               {$$ = newnode(Decimal, $1);}
    | LPAR Expr RPAR                                                        {$$ = $2;}
    ;

Aux_Expr: Expr                                                              {$$ = $1;}
        | Aux_Expr COMMA Expr                                               {$$ = $1; addchild($$, $3);}
        ;

%%

