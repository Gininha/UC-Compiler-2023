#!/bin/sh
./build.sh
./uccompiler < meta4/teste_bonk.c > teste_bonk.ll
lli teste_bonk.ll
./uccompiler < meta4/first.c > teste_bonk.ll
lli teste_bonk.ll | diff meta4/first.out -
./uccompiler < meta4/hello.c > teste_bonk.ll
lli teste_bonk.ll | diff meta4/hello.out -
./uccompiler < meta4/sierpinski.c > teste_bonk.ll
lli teste_bonk.ll | diff meta4/sierpinski.out -
./uccompiler < meta4/essential.c > teste_bonk.ll
lli teste_bonk.ll | diff meta4/essential.out -
./uccompiler < meta4/The_new_omg.c > teste_bonk.ll
lli teste_bonk.ll
./uccompiler < meta4/New_test_case.c > teste_bonk.ll
lli teste_bonk.ll
