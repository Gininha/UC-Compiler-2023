%{

#include "ast.h"

int yylex(void);
void yyerror(char *);

struct node *program;

%}


%token BITWISEAND BITWISEOR BITWISEXOR AND ASSIGN MUL COMMA DIV EQ GE GT LBRACE LE LPAR LT MINUS MOD
%token NE NOT OR PLUS RBRACE RPAR SEMI CHAR ELSE WHILE IF INT SHORT DOUBLE RETURN VOID

%token<token> CHRLIT IDENTIFIER NATURAL DECIMAL RESERVED


%type<node> program FunctionsAndDeclarations FunctionDefinition FunctionBody DeclarationsAndStatements
%type<node> FunctionDeclaration FunctionDeclarator ParameterList ParameterDeclaration Declaration
%type<node> TypeSpec Declarator Statement Expr

%union{
    char *token;
    struct node *node;
}

%%

%%

