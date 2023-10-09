/*
2020217743 Gustavo Samuel de Alves e Bastos de André e Lima
2021199102 Luis Miguel Gonçalves Leite
*/
%{
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>

    #define YY_USER_ACTION column += yyleng;
    #define ADDLINE line++; column=1;

    int line = 1, column = 1;
    int line_comm, column_comm;

    char *string = NULL;
%}

%X Comment

reserved                        auto|break|case|const|continue|default|do|enum|extern|float|for|goto|inline|long|register|restrict|signed|sizeof|static|struct|switch|typedef|union|unsigned|volatile|_Bool|_Complex|_Imaginary|"++"|"--"|"["|"]"
words                           char|else|while|if|int|short|double|return|void
digit                           [0-9]
decimal                         ([0-9]+"."(([eE][+-]?[0-9]+)|[0-9]+|([0-9]+[eE][+-]?[0-9]+))?)|("."[0-9]+([eE][+-]?[0-9]+)?)|([0-9]+([eE][+-]?[0-9]+))
identifier                      [a-zA-Z_][0-9a-zA-Z_]*
blank_spaces                    \t|\f|" "
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
{reserved}                      { printf("RESERVED(%s)\n", yytext); }
{words}                         { for(int i = 0; i < yyleng; i++) {yytext[i] = toupper(yytext[i]);} printf("%s\n", yytext); }
{digit}+                        { printf("NATURAL(%s)\n", yytext); }
{decimal}                       { printf("DECIMAL(%s)\n", yytext); }
{identifier}                    { printf("IDENTIFIER(%s)\n", yytext); }
{bitwiseand}                    { printf("BITWISEAND\n"); }
{bitwiseor}                     { printf("BITWISEOR\n"); }
{bitwisexor}                    { printf("BITWISEXOR\n"); }
{and}                           { printf("AND\n"); }
{assign}                        { printf("ASSIGN\n"); }
{mul}                           { printf("MUL\n"); }
{comma}                         { printf("COMMA\n"); }
{div}                           { printf("DIV\n"); }
{eq}                            { printf("EQ\n"); }
{ge}                            { printf("GE\n"); }
{gt}                            { printf("GT\n"); }
{lbrace}                        { printf("LBRACE\n"); }
{le}                            { printf("LE\n"); }
{lpar}                          { printf("LPAR\n"); }
{lt}                            { printf("LT\n"); }
{minus}                         { printf("MINUS\n"); }
{mod}                           { printf("MOD\n"); }
{ne}                            { printf("NE\n"); }
{not}                           { printf("NOT\n"); }
{or}                            { printf("OR\n"); }
{plus}                          { printf("PLUS\n"); }
{rbrace}                        { printf("RBRACE\n"); }
{rpar}                          { printf("RPAR\n"); }
{semi}                          { printf("SEMI\n"); }
{blank_spaces}                  { ; }
{new_line}                      { ADDLINE }
{begin_comment}                 { line_comm = line; column_comm = column - yyleng; BEGIN Comment; }
<Comment>{exit_comment}         { BEGIN 0; }
<Comment>{new_line}             { ADDLINE }
<Comment><<EOF>>                { printf("Line %d, column %d: unterminated comment\n", line_comm, column_comm); return 0; }
<Comment>.                      { ; }
{single_line_comm}              { ; }
'{charlit}'                     { printf("CHRLIT(%s)\n",yytext); }
{error_chrlit}                  { printf("Line %d, column %d: unterminated char constant\n", line, column - yyleng); ADDLINE }
{invalid_chrlit}                { printf("Line %d, column %d: invalid char constant (%s)\n", line, column - yyleng, yytext); }
<<EOF>>                         { return 0; }
.                               { printf("Line %d, column %d: unrecognized character (%s)\n",line, column - yyleng, yytext); }
%%

extern int yylex();
int main() {
    yylex();    /* run the lexical analysis automaton */
    return 0;
}
int yywrap() {  /* called on EOF, return 1 to terminate */
    return 1;
}