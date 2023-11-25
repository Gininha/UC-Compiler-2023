# UC-Compiler-2023 - Compilador para a linguagem UC

## Meta1
Contém todos os ficheiros necessários para a primeira entrega

## Meta2
Contém todos os ficheiros necessários para a segunda entrega

## src
Contém o código em desenvolvimento

## Sintaxe para compilar:
yacc -d -v -t -g --report=all uccompiler.y<br/>
lex uccompiler.l<br/>
cc -o uccompiler lex.yy.c y.tab.c ast.c -Wall -Wno-unused-function -g<br/>

## Sintaxe para testes:
./uccompiler < ficheiro.uc | diff ficheiro.out -
