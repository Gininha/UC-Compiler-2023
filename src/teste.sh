#!/bin/sh
./build.sh
echo '--- teste_bonk ---'
./uccompiler < meta4/teste_bonk.c > meta4/teste_bonk.ll
lli meta4/teste_bonk.ll | diff meta4/teste_bonk.out -
echo '--- first ---'
./uccompiler < meta4/first.c > meta4/first.ll
lli meta4/first.ll | diff meta4/first.out -
echo '--- hello ---'
./uccompiler < meta4/hello.c > meta4/hello.ll
lli meta4/hello.ll | diff meta4/hello.out -
echo '--- sierpinski ---'
./uccompiler < meta4/sierpinski.c > meta4/sierpinski.ll
lli meta4/sierpinski.ll | diff meta4/sierpinski.out -
echo '--- essential ---'
./uccompiler < meta4/essential.c > meta4/essential.ll
lli meta4/essential.ll | diff meta4/essential.out -
echo '--- The_new_omg ---'
./uccompiler < meta4/The_new_omg.c > meta4/The_new_omg.ll
lli meta4/The_new_omg.ll | diff meta4/The_new_omg.out -
echo '--- New_test_case ---'
./uccompiler < meta4/New_test_case.c > meta4/New_test_case.ll
lli meta4/New_test_case.ll | diff meta4/New_test_case.out -
