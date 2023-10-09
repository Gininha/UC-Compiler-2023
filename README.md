# UC-Compiler-2023 - Compilador para a linguagem UC
## Sintaxe para compilar:
lex uccompiler.l<br/>
cc lex.yy.c -o uccompiler<br/>
## sintaxe para testes:
./uccompiler < ficheiro.uc | diff ficheiro.out -