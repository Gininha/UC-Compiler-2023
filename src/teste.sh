#!/bin/sh
./build.sh
./uccompiler < meta4/teste_bonk.c > teste_bonk.ll
lli teste_bonk.ll
./uccompiler < meta4/first.c > first.ll
lli first.ll | diff meta4/first.out -
./uccompiler < meta4/hello.c > hello.ll
lli hello.ll | diff meta4/hello.out -
./uccompiler < meta4/sierpinski.c > sierpinski.ll
lli sierpinski.ll | diff meta4/sierpinski.out -
./uccompiler < meta4/essential.c > essential.ll
lli essential.ll | diff meta4/essential.out -

./uccompiler < meta4/New_test_case.c > New_test_case.ll
lli New_test_case.ll
