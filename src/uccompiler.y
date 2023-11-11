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
%type<node> TypeSpec Declarator Statement Expr Program Aux_Declaration StatList Aux_Expr StatList_aux

%union{
    char *token;
    struct node *node;
}

%left LOW
%left COMMA
%right ASSIGN
%right ELSE
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

%nonassoc LOWER
%nonassoc HIGHER

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
                                                                                addbrother($$, $2);

                                                                            }
                        | FunctionsAndDeclarations FunctionDeclaration      { 
                                                                                $$ = $1;    
                                                                                addbrother($$, $2);
                            
                                                                            }
                        | FunctionsAndDeclarations Declaration              { 
                                                                                $$ = $1;    
                                                                                addbrother($$, $2);

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
                                                                                $$ = $2;
                                                                            }
            | LBRACE RBRACE                                                 { $$ = newnode(FuncBody, NULL); }
            ;

DeclarationsAndStatements: DeclarationsAndStatements Statement              {   
                                                                                $$ = $1;
                                                                                if($2){
                                                                                    addchild($$, $2);
                                                                                }
                                                                            }
                         | DeclarationsAndStatements Declaration            {
                                                                                $$ = $1;
                                                                                addchild($$, $2);
                                                                            }
                         | Statement                                        {
                                                                                $$ = newnode(FuncBody, NULL);
                                                                                addchild($$, $1);
                                                                            }
                         | Declaration                                      {   
                                                                                $$ = newnode(FuncBody, NULL);
                                                                                addchild($$, $1);
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
                                                                                addbrother($$, $3);

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
                    | TypeSpec IDENTIFIER                                   {
                                                                                $$ = newnode(ParamDeclaration, NULL);
                                                                                addchild($$, $1);
                                                                                addchild($$, newnode(Identifier, $2));
                                                                            }
                    ;

Declaration: TypeSpec Declarator Aux_Declaration SEMI                       {
                                                                                $$ = newnode(Declaration, NULL);
                                                                                addchild($$, $1);
                                                                                addchild($$, $2);
                                                                                addbrother($$, $3);
                                                                                struct node_list* aux = $3->brotherhood;
                                                                                struct node_list* aux_children = $3->children;
                                                                                
                                                                                $3->children = malloc(sizeof(struct node_list));
                                                                                addchild($3, $1);
                                                                                while(aux_children != NULL){
                                                                                    addchild($3, aux_children->node);
                                                                                    aux_children = aux_children->next;
                                                                                }

                                                                                while(aux != NULL){
                                                                                    aux_children = aux->node->children;
                                                                                    aux->node->children = malloc(sizeof(struct node_list));
                                                                                    addchild(aux->node, $1);

                                                                                    while(aux_children != NULL){
                                                                                        addchild(aux->node, aux_children->node);
                                                                                        aux_children = aux_children->next;
                                                                                    }

                                                                                    aux = aux->next;
                                                                                }  
                                                                            }
           | TypeSpec Declarator SEMI                                       {
                                                                                $$ = newnode(Declaration, NULL);
                                                                                addchild($$, $1);
                                                                                addchild($$, $2);
                                                                            }

Aux_Declaration: COMMA Declarator                                           {
                                                                                $$ = newnode(Declaration, NULL);
                                                                                addchild($$, $2);
                                                                            }
               | Aux_Declaration COMMA Declarator                           {
                                                                                $$ = $1;
                                                                                struct node* temp = newnode(Declaration, NULL);
                                                                                addchild(temp, $3);
                                                                                addbrother($$, temp);
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
                                                                                addbrother($$, $3);
                                                                            }
          ;

Statement: Expr SEMI                                                        { $$ = $1; }
         | SEMI                                                             { $$ = NULL; }
         | LBRACE RBRACE                                                    { $$ = NULL; }
         | LBRACE StatList RBRACE                                           { $$ = $2; }
         | IF LPAR Expr RPAR Statement                       %prec LOW      { 
                                                                                $$ = newnode(If, NULL); 
                                                                                addchild($$, $3);
                                                                                if($5){ 
                                                                                    addchild($$, $5);
                                                                                }else{ 
                                                                                    addchild($$, newnode(Null, NULL));
                                                                                }
                                                                                addchild($$, newnode(Null, NULL));
                                                                            }      
         | IF LPAR Expr RPAR Statement ELSE Statement                       { 
                                                                                $$ = newnode(If, NULL); 
                                                                                addchild($$, $3);
                                                                                if($5){ 
                                                                                    addchild($$, $5);
                                                                                }else{ 
                                                                                    addchild($$, newnode(Null, NULL));
                                                                                }
                                                                                if($7){
                                                                                    addchild($$, $7);
                                                                                }else{ 
                                                                                    addchild($$, newnode(Null, NULL));
                                                                                }
                                                                            }

         | WHILE LPAR Expr RPAR Statement                                   {   
                                                                                $$ = newnode(While, NULL); 
                                                                                addchild($$, $3); 
                                                                                if($5){
                                                                                    addchild($$, $5);
                                                                                }else{
                                                                                    addchild($$, newnode(Null, NULL));
                                                                                } 
                                                                            }
         | RETURN SEMI                                                      { $$ = newnode(Return, NULL); addchild($$, newnode(Null, NULL)); }
         | RETURN Expr SEMI                                                 { $$ = newnode(Return, NULL); addchild($$, $2);}
         ;

StatList: Statement                                                         { 
                                                                                $$ = $1;
                                                                            }
        | StatList_aux Statement                                            {
                                                                                $$ = newnode(StatList, NULL);
                                                                                addchild($$, $1);
                                                                                addchild($$, $2);
                                                                            }
        ;

StatList_aux:Statement                                                      { 
                                                                                $$ = $1;
                                                                            }
            | StatList_aux Statement                                        {
                                                                                $$ = $1;
                                                                                addbrother($$, $2);
                                                                            }
            ;

Expr: Expr ASSIGN Expr                                                      {$$ = newnode(Store, NULL); addchild($$, $1); addchild($$, $3);}
    | Expr COMMA Expr                                                       {$$ = newnode(Comma, NULL); addchild($$, $1); addchild($$, $3);}
    | Expr PLUS Expr                                                        {$$ = newnode(Add, NULL); addchild($$, $1); addchild($$, $3);}
    | Expr MINUS Expr                                                       {$$ = newnode(Minus, NULL); addchild($$, $1); addchild($$, $3);}
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
    | PLUS Expr        %prec NOT                                            {$$ = newnode(Add, NULL); addchild($$, $2);}
    | MINUS Expr       %prec NOT                                            {$$ = newnode(Minus, NULL); addchild($$, $2);}
    | NOT Expr                                                              {$$ = newnode(Not, NULL); addchild($$, $2);}
    | IDENTIFIER LPAR RPAR                                                  {$$ = newnode(Call, NULL); addchild($$, newnode(Identifier, $1)); addchild($$, newnode(Null, NULL));}
    | IDENTIFIER LPAR Aux_Expr RPAR                                         {$$ = newnode(Call, NULL); addchild($$, newnode(Identifier, $1)); addchild($$, $3);}
    | IDENTIFIER                                                            {$$ = newnode(Identifier, $1);}
    | NATURAL                                                               {$$ = newnode(Natural, $1);}
    | CHRLIT                                                                {$$ = newnode(ChrLit, $1);}
    | DECIMAL                                                               {$$ = newnode(Decimal, $1);}
    | LPAR Expr RPAR                                                        {$$ = $2;}
    ;

Aux_Expr: Expr                         %prec LOWER                          {$$ = $1;}
        | Aux_Expr COMMA Expr          %prec HIGHER                         {$$ = $1; addbrother($$, $3);}
        ;

%%

