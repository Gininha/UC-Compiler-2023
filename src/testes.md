# Neste ficheiro estao os testes q foram testados



###### --------------------------------------------------------------------------------------------------

### Meta 2

# cenas (a funcionar)

./uccompiler -t < meta2/first.c | diff meta2/first.out -
./uccompiler -t < meta2/test_statementsAST.uc | diff meta2/test_statementsAST.out -
./uccompiler -t < meta2/StatLists.uc | diff meta2/StatLists.out -
./uccompiler -t < meta2/AST_Statements.uc | diff meta2/AST_Statements.out -
./uccompiler -t < meta2/DeclarationTests.uc | diff meta2/DeclarationTests.out -
./uccompiler -t < meta2/fdeclarations.uc | diff meta2/fdeclarations.out -
./uccompiler -t < meta2/more_stmt_errors.uc | diff meta2/more_stmt_errors.out -
./uccompiler -t < meta2/multiple_tests.uc | diff meta2/multiple_tests.out -
./uccompiler -t < meta2/rb_declarations_01.uc | diff meta2/rb_declarations_01.out -
./uccompiler -t < meta2/rb_expressions_01.uc | diff meta2/rb_expressions_01.out -                                       
./uccompiler -t < meta2/ReturnComma.uc | diff meta2/ReturnComma.out -
./uccompiler -t < meta2/sierpinski.c | diff meta2/sierpinski.out -
./uccompiler -t < meta2/statements_and_lexical_errors.uc | diff meta2/statements_and_lexical_errors.out -               
./uccompiler -t < meta2/statements_test.uc | diff meta2/statements_test.out -                                           
./uccompiler -t < meta2/statements.uc | diff meta2/statements.out -                                                     
./uccompiler -t < meta2/factorials.uc | diff meta2/factorials.out -                     
./uccompiler -t < meta2/miscellaneous_test.uc | diff meta2/miscellaneous_test.out -        


# erros (a funcionar)

./uccompiler -t < meta2/DecDefErrors.uc | diff meta2/DecDefErrors.out -
./uccompiler -t < meta2/declarations.uc | diff meta2/declarations.out -
./uccompiler -t < meta2/errors.uc | diff meta2/errors.out -
./uccompiler -t < meta2/errors2_2.uc | diff meta2/errors2_2.out -
./uccompiler -t < meta2/expr_test.uc | diff meta2/expr_test.out -
./uccompiler -t < meta2/expressions.uc | diff meta2/expressions.out -
./uccompiler -t < meta2/StatementsErrors.uc | diff meta2/StatementsErrors.out -
./uccompiler -t < meta2/syntax_errors.uc | diff meta2/syntax_errors.out -
./uccompiler -t < meta2/empty_with_spaces.uc | diff meta2/empty_with_spaces.out -           
./uccompiler -t < meta2/test_emptyComments.uc | diff meta2/test_emptyComments.out -         
./uccompiler -t < meta2/test_emptySpaces.uc | diff meta2/test_emptySpaces.out -             
./uccompiler -t < meta2/zerobytes.uc | diff meta2/zerobytes.out -                           


# resto (a nao funcionar)

# All Working !!!

###### --------------------------------------------------------------------------------------------------

### Meta 3


# A funcionar

./uccompiler -s < meta3/start_here.uc | diff meta3/start_here.out -
./uccompiler -s < meta3/symboltables.uc | diff meta3/symboltables.out -
./uccompiler -s < meta3/first.c | diff meta3/first.out -                                    
./uccompiler -s < meta3/semantic_errors.uc | diff meta3/semantic_errors.out -                
./uccompiler -s < meta3/errors_funcdefinitions.uc | diff meta3/errors_funcdefinitions.out -  


# A nao funcionar

./uccompiler -s < meta3/expression.c | diff meta3/expression.out -                           // Tambem so falta erros


# Depressao

./uccompiler -s < meta3/erros.uc | diff meta3/erros.out -       // Este da seg fault
