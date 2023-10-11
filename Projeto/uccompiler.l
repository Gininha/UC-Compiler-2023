/*
2020217743 Gustavo Samuel de Alves e Bastos de André e Lima
2021199102 Luis Miguel Gonçalves Leite
*/
%{
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>

    #define YY_USER_ACTION column += yyleng;
    #define ADDLINE line++; column = 1;

    int l = 0;

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
{reserved}                      { if (l) printf("RESERVED(%s)\n", yytext); }
{words}                         { if (l) {{for(int i = 0; i < yyleng; i++) {yytext[i] = toupper(yytext[i]);} printf("%s\n", yytext); }} }
{digit}+                        { if (l) printf("NATURAL(%s)\n", yytext); }
{decimal}                       { if (l) printf("DECIMAL(%s)\n", yytext); }
{identifier}                    { if (l) printf("IDENTIFIER(%s)\n", yytext); }
{bitwiseand}                    { if (l) printf("BITWISEAND\n"); }
{bitwiseor}                     { if (l) printf("BITWISEOR\n"); }
{bitwisexor}                    { if (l) printf("BITWISEXOR\n"); }
{and}                           { if (l) printf("AND\n"); }
{assign}                        { if (l) printf("ASSIGN\n"); }
{mul}                           { if (l) printf("MUL\n"); }
{comma}                         { if (l) printf("COMMA\n"); }
{div}                           { if (l) printf("DIV\n"); }
{eq}                            { if (l) printf("EQ\n"); }
{ge}                            { if (l) printf("GE\n"); }
{gt}                            { if (l) printf("GT\n"); }
{lbrace}                        { if (l) printf("LBRACE\n"); }
{le}                            { if (l) printf("LE\n"); }
{lpar}                          { if (l) printf("LPAR\n"); }
{lt}                            { if (l) printf("LT\n"); }
{minus}                         { if (l) printf("MINUS\n"); }
{mod}                           { if (l) printf("MOD\n"); }
{ne}                            { if (l) printf("NE\n"); }
{not}                           { if (l) printf("NOT\n"); }
{or}                            { if (l) printf("OR\n"); }
{plus}                          { if (l) printf("PLUS\n"); }
{rbrace}                        { if (l) printf("RBRACE\n"); }
{rpar}                          { if (l) printf("RPAR\n"); }
{semi}                          { if (l) printf("SEMI\n"); }
{blank_spaces}                  { ; }
{new_line}                      { ADDLINE }
{begin_comment}                 { line_comm = line; column_comm = column - yyleng; BEGIN Comment; }
<Comment>{exit_comment}         { BEGIN 0; }
<Comment>{new_line}             { ADDLINE }
<Comment><<EOF>>                { printf("Line %d, column %d: unterminated comment\n", line_comm, column_comm); return 0; }
<Comment>.                      { ; }
{single_line_comm}              { ; }
'{charlit}'                     { if (l) printf("CHRLIT(%s)\n",yytext); }
{error_chrlit}                  { printf("Line %d, column %d: unterminated char constant\n", line, column - yyleng); ADDLINE }
{invalid_chrlit}                { printf("Line %d, column %d: invalid char constant (%s)\n", line, column - yyleng, yytext); }
<<EOF>>                         { return 0; }
.                               { printf("Line %d, column %d: unrecognized character (%s)\n",line, column - yyleng, yytext); }
%%

extern int yylex();
int main(int argc, char * argv[]) {
    if (argc > 1)
        if (strcmp(argv[1], "-l") == 0)
            l = 1;

    yylex();    /* run the lexical analysis automaton */
    return 0;
}
int yywrap() {  /* called on EOF, return 1 to terminate */
    return 1;
}