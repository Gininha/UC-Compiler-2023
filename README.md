# UC-Compiler-2023 - Compilador para a linguagem UC
## Sintaxe para compilar:
yacc -dv uccompiler.y<br/>
lex uccompiler.l<br/>
cc lex.yy.c -o uccompiler<br/>
## Sintaxe para testes:
./uccompiler < ficheiro.uc | diff ficheiro.out -
