Neste ficheiro estao os testes q foram testados e passados

./uccompiler -t < meta2/first.c | diff meta2/first.out -
./uccompiler -t < meta2/test_statementsAST.uc | diff meta2/test_statementsAST.out -
./uccompiler -t < meta2/StatLists.uc | diff meta2/StatLists.out -
./uccompiler -t < meta2/AST_Statements.uc | diff meta2/AST_Statements.out -
./uccompiler -t < meta2/DeclarationTests.uc | diff meta2/DeclarationTests.out -