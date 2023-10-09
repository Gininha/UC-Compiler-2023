%{
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>

    int flag = 0;       //flag se houver erro na charlit
    int line = 1;
    int column = 1;
    int line_comm = 0;
    int column_comm = 1;
    char *string = NULL;
%}

%X Comment

reserved                        auto|break|case|const|continue|default|do|enum|extern|float|for|goto|inline|long|register|restrict|signed|sizeof|static|struct|switch|typedef|union|unsigned|volatile|_Bool|_Complex|_Imaginary|"++"|"--"|"["|"]"
words                           char|else|while|if|int|short|double|return|void
digit                           [0-9]
decimal                         ([0-9]+"."(([eE][+-]?[0-9]+)|[0-9]+|([0-9]+[eE][+-]?[0-9]+))?)|("."[0-9]+([eE][+-]?[0-9]+)?)|([0-9]+([eE][+-]?[0-9]+))
identifier                      [a-zA-Z_][0-9a-zA-Z_]*
blank_spaces                    \t|\n|" "|"\r"
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
{reserved}                      { printf("RESERVED(%s)\n", yytext); column+=strlen(yytext);}
{words}                         { for(int i=0; i<yyleng; i++){yytext[i] = toupper(yytext[i]);}printf("%s\n", yytext); column += strlen(yytext);}
{digit}+                        { printf("NATURAL(%s)\n", yytext); column+=strlen(yytext);}
{decimal}                       { printf("DECIMAL(%s)\n", yytext); column+=strlen(yytext);}
{identifier}                    { printf("IDENTIFIER(%s)\n", yytext); column+=strlen(yytext);}
{bitwiseand}                    { printf("BITWISEAND\n"); column += strlen(yytext);}
{bitwiseor}                     { printf("BITWISEOR\n"); column += strlen(yytext);}
{bitwisexor}                    { printf("BITWISEXOR\n"); column += strlen(yytext);}
{and}                           { printf("AND\n"); column += strlen(yytext);}
{assign}                        { printf("ASSIGN\n"); column += strlen(yytext);}
{mul}                           { printf("MUL\n"); column += strlen(yytext);}
{comma}                         { printf("COMMA\n"); column += strlen(yytext);}
{div}                           { printf("DIV\n"); column += strlen(yytext);}
{eq}                            { printf("EQ\n"); column += strlen(yytext);}
{ge}                            { printf("GE\n"); column += strlen(yytext);}
{gt}                            { printf("GT\n"); column += strlen(yytext);}
{lbrace}                        { printf("LBRACE\n"); column += strlen(yytext);}
{le}                            { printf("LE\n"); column += strlen(yytext);}
{lpar}                          { printf("LPAR\n"); column += strlen(yytext);}
{lt}                            { printf("LT\n"); column += strlen(yytext);}
{minus}                         { printf("MINUS\n"); column += strlen(yytext);}
{mod}                           { printf("MOD\n"); column += strlen(yytext);}
{ne}                            { printf("NE\n"); column += strlen(yytext);}
{not}                           { printf("NOT\n"); column += strlen(yytext);}
{or}                            { printf("OR\n"); column += strlen(yytext);}
{plus}                          { printf("PLUS\n"); column += strlen(yytext);}
{rbrace}                        { printf("RBRACE\n"); column += strlen(yytext);}
{rpar}                          { printf("RPAR\n"); column += strlen(yytext);}
{semi}                          { printf("SEMI\n"); column += strlen(yytext);}
{blank_spaces}                  { if(strcmp(yytext, "\n") == 0){line++; column = 1;}else{column += strlen(yytext);}}
{begin_comment}                 { line_comm = line; column_comm = column; column += strlen(yytext); BEGIN Comment;}
<Comment>{exit_comment}         { column += strlen(yytext); BEGIN 0;}
<Comment>{blank_spaces}         { if(strcmp(yytext, "\n") == 0){line++; column = 1;}else{column += strlen(yytext);}}
<Comment><<EOF>>                { printf("Line %d, column %d: unterminated comment\n", line_comm, column_comm); BEGIN 0;}
<Comment>.                      { column += strlen(yytext);}
{single_line_comm}              ;
'{charlit}'                     { printf("CHRLIT(%s)\n",yytext); column+=strlen(yytext);}
{error_chrlit}                  { printf("Line %d, column %d: unterminated char constant\n", line, column); column=1; line++;}
{invalid_chrlit}                { printf("Line %d, column %d: invalid char constant (%s)\n", line, column, yytext); column+=strlen(yytext);}
.                               { printf("Line %d, column %d: unrecognized character (%s)\n",line, column, yytext); column+=strlen(yytext);}
%%

extern int yylex();
int main() {
    yylex();    /* run the lexical analysis automaton */
    return 0;
}
int yywrap() {  /* called on EOF, return 1 to terminate */
    return 1;
}