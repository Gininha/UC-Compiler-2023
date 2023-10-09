# UC-Compiler-2023
 Compilador para a linguagem UC

 Sintaxe para compilar:
 lex uccompiler.l
 cc lex.yy.c -o uccompiler
 
 Sintaxe para testes:
 ./uccompiler < ficheiro.uc | diff ficheiro.out -