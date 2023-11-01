%{

#include "ast.h"

int yylex(void);
void yyerror(char *);

struct node *program;

%}


%token BITWISEAND BITWISEOR BITWISEXOR AND ASSIGN MUL COMMA DIV EQ GE GT LBRACE LE LPAR LT MINUS MOD
%token NE NOT OR PLUS RBRACE RPAR SEMI CHAR ELSE WHILE IF INT SHORT DOUBLE RETURN VOID

%token<token> CHRLIT IDENTIFIER NATURAL DECIMAL RESERVED


%type<node> FunctionsAndDeclarations FunctionDefinition FunctionBody DeclarationsAndStatements
%type<node> FunctionDeclaration FunctionDeclarator ParameterList ParameterDeclaration Declaration
%type<node> TypeSpec Declarator Statement Expr

%union{
    char *token;
    struct node *node;
}

%left LOW
%left COMMA
%right assign
%left OR
%left AND
%left bitwiseor
%left bitwisexor
%left bitwiseand
%left EQ NE
%left GT LE GE LT
%left PLUS MINUS
%left MUL DIV MOD
%right NOT
%left LPAR RPAR '[' ']'

%%

FunctionsAndDeclarations: FunctionDefinition                                {}
                        | FunctionDeclaration                               {}
                        | Declaration                                       {}
                        | FunctionsAndDeclarations FunctionDefinition       {}
                        | FunctionsAndDeclarations FunctionDeclaration      {}
                        | FunctionsAndDeclarations Declaration              {}
                        ;

FunctionDefinition: TypeSpec FunctionDeclarator FunctionBody                {}
                  ;

FunctionBody: LBRACE DeclarationsAndStatements RBRACE                       {}
            | LBRACE RBRACE                                                 {}
            ;

DeclarationsAndStatements: Statement DeclarationsAndStatements              {}
                         | Declaration DeclarationsAndStatements            {}
                         | Statement                                        {}
                         | Declaration                                      {}
                         ;

FunctionDeclaration: TypeSpec FunctionDeclarator SEMI                       {}
                   ;

FunctionDeclarator: IDENTIFIER LPAR ParameterList RPAR                      {}
                  ;

ParameterList: ParameterDeclaration                                         {}
             | ParameterList COMMA ParameterDeclaration                     {}
             ; 

ParameterDeclaration: TypeSpec                                              {}
                    | TypeSpec IDENTIFIER                                   {}
                    ;

Declaration: TypeSpec Declarator SEMI                                       {}
           | TypeSpec Declarator Aux_Declaration SEMI                       {}
           ;

Aux_Declaration: COMMA Declarator                                           {}
               | Aux_Declaration COMMA Declarator                           {}
               ;

TypeSpec: CHAR                                                              {}
        | INT                                                               {}
        | VOID                                                              {}
        | SHORT                                                             {}
        | DOUBLE                                                            {}
        ;

Declarator: IDENTIFIER                                                      {}
          | IDENTIFIER ASSIGN Expr                                          {}
          ;

Statement: Expr SEMI                                                        {}
         | SEMI                                                             {}
         | LBRACE RBRACE                                                    {}
         | LBRACE Aux_Statement RBRACE                                      {}
         | IF LPAR Expr RPAR Statement                       %prec LOW      {}      
         | IF LPAR Expr RPAR Statement ELSE Statement                       {}
         | WHILE LPAR Expr RPAR Statement                                   {}
         | RETURN SEMI                                                      {}
         | RETURN Expr SEMI                                                 {}
         ;

Aux_Statement: Statement                                                    {}
             | Aux_Statement Statement                                      {}
             ;

Expr: Expr ASSIGN Expr                                                      {}
    | Expr COMMA Expr                                                       {}
    | Expr PLUS Expr                                                        {}
    | Expr MINUS Expr                                                       {}
    | Expr MUL Expr                                                         {}
    | Expr DIV Expr                                                         {}
    | Expr MOD Expr                                                         {}
    | Expr OR Expr                                                          {}
    | Expr AND Expr                                                         {}
    | Expr BITWISEAND Expr                                                  {}
    | Expr BITWISEOR Expr                                                   {}
    | Expr BITWISEXOR Expr                                                  {}
    | Expr EQ Expr                                                          {}
    | Expr NE Expr                                                          {}
    | Expr LE Expr                                                          {}
    | Expr GE Expr                                                          {}
    | Expr LT Expr                                                          {}
    | Expr GT Expr                                                          {}
    | PLUS Expr                                                             {}
    | MINUS Expr                                                            {}
    | NOT Expr                                                              {}
    | IDENTIFIER LPAR RPAR                                                  {}
    | IDENTIFIER LPAR Aux_Expr RPAR                                         {}
    | IDENTIFIER                                                            {}
    | NATURAL                                                               {}
    | CHRLIT                                                                {}
    | DECIMAL                                                               {}
    | LPAR Expr RPAR                                                        {}
    ;

Aux_Expr: Expr 
        | Aux_Expr COMMA Expr                                               {}
        ;

%%

