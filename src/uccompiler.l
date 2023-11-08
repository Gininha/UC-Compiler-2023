/*
2020217743 Gustavo Samuel de Alves e Bastos de André e Lima
2021199102 Luis Miguel Gonçalves Leite
*/
%{
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>
    
    #include "y.tab.h"
    #include "ast.h"

    #define YY_USER_ACTION {y_line = line; y_column = column; column += yyleng;}
    #define ADDLINE line++; column = 1;
    #define PASS_TOKEN() yylval.token = strdup(yytext);

    int yyparse(void);
    void yyerror(char *);

    int l = 0;
    int y = 0;

    int line = 1, column = 1, y_line = -1, y_column = -1;
    int line_comm, column_comm;

    char *string = NULL;

    extern struct node *program;
%}

%X Comment

reserved                        auto|break|case|const|continue|default|do|enum|extern|float|for|goto|inline|long|register|restrict|signed|sizeof|static|struct|switch|typedef|union|unsigned|volatile|_Bool|_Complex|_Imaginary|"++"|"--"|"["|"]"
digit                           [0-9]
decimal                         ([0-9]+"."(([eE][+-]?[0-9]+)|[0-9]+|([0-9]+[eE][+-]?[0-9]+))?)|("."[0-9]+([eE][+-]?[0-9]+)?)|([0-9]+([eE][+-]?[0-9]+))
identifier                      [a-zA-Z_][0-9a-zA-Z_]*
blank_spaces                    \t|" "
new_line                        "\n"|"\r"|"\r\n"
begin_comment                   "/*"
exit_comment                    "*/"
charlit                         [^\n\'\\]|\\n|\\t|\\\\|\\\'|\\\"|\\[0-7]?[0-7]?[0-7]?
error_chrlit                    '([^\n\'\\]|\\.)*\\?("\n"|"\r\n"|"\r")?
invalid_chrlit                  '([^\n\'\\]|\\.)*'
single_line_comm                "//"[^\n\r]*
bitwiseand                      "&"
bitwiseor                       "|"
bitwisexor                      "^"
and                             "&&"
assign                          "="
mul                             "*"
comma                           ","
div                             "/"
eq                              "=="
ge                              ">="
gt                              ">"
lbrace                          "{"
le                              "<="
lpar                            "("
lt                              "<"
minus                           "-"
mod                             "%"
ne                              "!="
not                             "!"
or                              "||"
plus                            "+"
rbrace                          "}"
rpar                            ")"
semi                            ";"

%%
{reserved}                      { if (l) printf("RESERVED(%s)\n", yytext); if(y){ PASS_TOKEN(); return RESERVED;} }
char                            { if (l) printf("CHAR\n"); if(y) return CHAR;}
else                            { if (l) printf("ELSE\n"); if(y) return ELSE;}
while                           { if (l) printf("WHILE\n"); if(y) return WHILE;}
if                              { if (l) printf("IF\n"); if(y) return IF;}
int                             { if (l) printf("INT\n"); if(y) return INT;}
short                           { if (l) printf("SHORT\n"); if(y) return SHORT;}
double                          { if (l) printf("DOUBLE\n"); if(y) return DOUBLE;}
return                          { if (l) printf("RETURN\n"); if(y) return RETURN;}
void                            { if (l) printf("VOID\n"); if(y) return VOID;}
{digit}+                        { if (l) printf("NATURAL(%s)\n", yytext); if(y){ PASS_TOKEN(); return NATURAL;} }
{decimal}                       { if (l) printf("DECIMAL(%s)\n", yytext); if(y){ PASS_TOKEN(); return DECIMAL;} }
{identifier}                    { if (l) printf("IDENTIFIER(%s)\n", yytext); if(y){ PASS_TOKEN(); return IDENTIFIER;} }
{bitwiseand}                    { if (l) printf("BITWISEAND\n"); if(y) return BITWISEAND; }
{bitwiseor}                     { if (l) printf("BITWISEOR\n"); if(y) return BITWISEOR; }
{bitwisexor}                    { if (l) printf("BITWISEXOR\n"); if(y) return BITWISEXOR; }
{and}                           { if (l) printf("AND\n"); if(y) return AND; }
{assign}                        { if (l) printf("ASSIGN\n"); if(y) return ASSIGN; }
{mul}                           { if (l) printf("MUL\n"); if(y) return MUL; }
{comma}                         { if (l) printf("COMMA\n"); if(y) return COMMA; }
{div}                           { if (l) printf("DIV\n"); if(y) return DIV; }
{eq}                            { if (l) printf("EQ\n"); if(y) return EQ; }
{ge}                            { if (l) printf("GE\n"); if(y) return GE; }
{gt}                            { if (l) printf("GT\n"); if(y) return GT; }
{lbrace}                        { if (l) printf("LBRACE\n"); if(y) return LBRACE; }
{le}                            { if (l) printf("LE\n"); if(y) return LE; }
{lpar}                          { if (l) printf("LPAR\n"); if(y) return LPAR; }
{lt}                            { if (l) printf("LT\n"); if(y) return LT; }
{minus}                         { if (l) printf("MINUS\n"); if(y) return MINUS; }
{mod}                           { if (l) printf("MOD\n"); if(y) return MOD; }
{ne}                            { if (l) printf("NE\n"); if(y) return NE; }
{not}                           { if (l) printf("NOT\n"); if(y) return NOT; }
{or}                            { if (l) printf("OR\n"); if(y) return OR; }
{plus}                          { if (l) printf("PLUS\n"); if(y) return PLUS; }
{rbrace}                        { if (l) printf("RBRACE\n"); if(y) return RBRACE; }
{rpar}                          { if (l) printf("RPAR\n"); if(y) return RPAR; }
{semi}                          { if (l) printf("SEMI\n"); if(y) return SEMI; }
{blank_spaces}                  { ; }
{new_line}                      { ADDLINE }
{begin_comment}                 { line_comm = line; column_comm = column - yyleng; BEGIN Comment; }
<Comment>{exit_comment}         { BEGIN 0; }
<Comment>{new_line}             { ADDLINE }
<Comment><<EOF>>                { printf("Line %d, column %d: unterminated comment\n", line_comm, column_comm); return 0; }
<Comment>.                      { ; }
{single_line_comm}              { ; }
'{charlit}'                     { if (l) printf("CHRLIT(%s)\n",yytext); if(y){ PASS_TOKEN() return CHRLIT;} }
{error_chrlit}                  { printf("Line %d, column %d: unterminated char constant\n", line, column - yyleng); ADDLINE }
{invalid_chrlit}                { printf("Line %d, column %d: invalid char constant (%s)\n", line, column - yyleng, yytext); }
<<EOF>>                         { return 0; }
.                               { printf("Line %d, column %d: unrecognized character (%s)\n",line, column - yyleng, yytext); }
%%

extern int yylex();
int main(int argc, char * argv[]) {
    
    if (argc > 1){
        if (strcmp(argv[1], "-l") == 0)
            l = 1;
        if (strcmp(argv[1], "-t") == 0)
            y = 1;
    }
    y = 1;
    yyparse();
    show(program, 0);
    return 0;
}

int yywrap() {  /* called on EOF, return 1 to terminate */
    return 1;
}

void yyerror (char *error) {
    printf("Line %d column %d: %s: %s\n" , y_line, y_column, error, yytext);
}
