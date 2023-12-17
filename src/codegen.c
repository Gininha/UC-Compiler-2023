#include "codegen.h"
#include "ast.h"
#include "semantics.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int temporary;

extern struct symbol_list *symbol_table;

int get_value(char *string) {
    int char_value = 0;
    char aux[7] = "\\";
    int pos = 2;
    if (string) {
        if (string[1] == '\\') {
            if (string[2] == 'n') {
                char_value = '\n';
            } else {
                while (string[pos] != '\'') {
                    aux[pos - 2] = string[pos];
                    pos++;
                }
                aux[pos - 2] = '\0';

                sscanf(aux, "%o", &char_value);
            }
        } else {
            char_value = string[1];
        }
    }

    return char_value;
}

int codegen_add(struct node *add) {
    int e1 = codegen_expression(getchild(add, 0));
    int e2 = codegen_expression(getchild(add, 1));
    printf("  %%%d = add i32 %%%d, %%%d\n", temporary, e1, e2);

    return temporary++;
}

int codegen_sub(struct node *sub) {
    int e1 = codegen_expression(getchild(sub, 0));
    int e2 = codegen_expression(getchild(sub, 1));
    printf("  %%%d = sub i32 %%%d, %%%d\n", temporary, e1, e2);
    return temporary++;
}

int codegen_mul(struct node *mul) {
    int e1 = codegen_expression(getchild(mul, 0));
    int e2 = codegen_expression(getchild(mul, 1));
    printf("  %%%d = mul i32 %%%d, %%%d\n", temporary, e1, e2);
    return temporary++;
}

int codegen_div(struct node *div) {
    int e1 = codegen_expression(getchild(div, 0));
    int e2 = codegen_expression(getchild(div, 1));
    printf("  %%%d = sdiv i32 %%%d, %%%d\n", temporary, e1, e2);
    return temporary++;
}

int codegen_natural(struct node *natural) {
    printf("  %%%d = add i32 %s, 0\n", temporary, natural->token);
    return temporary++;
}

int codegen_decimal(struct node *decimal) {
    printf("  %%%d = fadd double %s, 0.0\n", temporary, decimal->token);
    return temporary++;
}

int codegen_identifier(struct node *identifier) {

    if (search_symbol(symbol_table, identifier->token)) // Variavel global
        printf("  %%%d = load i32, i32* @%s\n", temporary, identifier->token);
    else
        printf("  %%%d = load i32, i32* %%_%s\n", temporary, identifier->token);

    return temporary++;
}

int codegen_call(struct node *call) {
    struct node_list *arguments = call->children->next;
    struct node *aux = call->children->next->node;
    char *arguments_str = malloc(1);
    *arguments_str = '\0';
    int curr = 1;
    while ((arguments = arguments->next) != NULL) {
        int e = codegen_expression(arguments->node);
        char str[18];
        if (curr > 1)
            sprintf(str, ", i32 %%%d", e);
        else
            sprintf(str, "i32 %%%d", e);
        arguments_str = realloc(arguments_str, strlen(arguments_str) + strlen(str) + 1);
        strcat(arguments_str, str);
        curr++;
    }
    if ((strcmp(aux->token, "putchar") == 0) || (strcmp(aux->token, "getchar") == 0))
        printf("  %%%d = tail call i32 @%s(%s)\n", temporary, getchild(call, 0)->token, arguments_str);
    else {
        if (aux->type == integer_type || aux->type == short_type || aux->type == char_type)
            printf("  %%%d = tail call i32 @_%s(%s)\n", temporary, getchild(call, 0)->token, arguments_str);
        if (aux->type == double_type)
            printf("  %%%d = tail call double @_%s(%s)\n", temporary, getchild(call, 0)->token, arguments_str);
        if (aux->type == void_type) {
            printf("  tail call void @_%s(%s)\n", getchild(call, 0)->token, arguments_str);
            temporary--;
        }
    }
    return temporary++;
}

int codegen_ifthenelse(struct node *ifthenelse) {
    int label_id = temporary++;
    printf("  %%%d = alloca i32\n", label_id);
    int e = codegen_expression(getchild(ifthenelse, 0));
    printf("  %%%d = icmp ne i32 %%%d, 0\n", temporary, e);
    printf("  br i1 %%%d, label %%L%dthen, label %%L%delse\n", temporary++, label_id, label_id);

    printf("L%dthen:\n", label_id);
    int e1 = codegen_expression(getchild(ifthenelse, 1));
    if (e1 != -1) {
        printf("  store i32 %%%d, i32* %%%d\n", e1, label_id);
        printf("  br label %%L%dend\n", label_id);
    } else
        printf("  br label %%L%dend\n", label_id);

    printf("L%delse:\n", label_id);
    int e2 = codegen_expression(getchild(ifthenelse, 2));
    if (e2 != -1) {
        printf("  store i32 %%%d, i32* %%%d\n", e2, label_id);
        printf("  br label %%L%dend\n", label_id);
    } else
        printf("  br label %%L%dend\n", label_id);

    printf("L%dend:\n", label_id);
    printf("  %%%d = load i32, i32* %%%d\n", temporary, label_id);
    return temporary++;
}

int codegen_while(struct node *while_node) {
    int label_id = temporary;

    // Loop condition
    printf("  br label %%L%d\n", label_id);
    printf("L%d:\n", label_id);

    int condition_result = codegen_expression(getchild(while_node, 0));
    printf("  br i1 %%%d, label %%L%dBody, label %%L%dEnd\n", condition_result, label_id, label_id);

    // Loop body
    printf("L%dBody:\n", label_id);
    codegen_expression(getchild(while_node, 1));

    // Loop back to condition
    printf("  br label %%L%d\n", label_id);

    // Loop end
    printf("L%dEnd:\n", label_id);

    return temporary;
}

int codegen_declaration(struct node *declaration) {
    struct node *type_node = getchild(declaration, 0);
    struct node *identifier_node = getchild(declaration, 1);
    struct node *value_node = getchild(declaration, 2);
    // Map UC data types to LLVM IR types
    const char *llvm_type;
    if (type_node->category == Int || type_node->category == Short || type_node->category == Char) {
        llvm_type = "i32";
    } else if (type_node->category == Double) {
        llvm_type = "double";
    }

    printf("  %%_%s = alloca %s\n", identifier_node->token, llvm_type);

    // Code generation for initializing with a constant value (if provided)
    if (value_node != NULL) {

        int teste = codegen_expression(value_node);

        printf("  store %s %%%d, %s* %%_%s\n", llvm_type, teste, llvm_type, identifier_node->token);
    }

    return temporary;
}

int codegen_return(struct node *return_node) {
    struct node *return_value = getchild(return_node, 0);

    // Code generation for the return value
    int return_value_tmp = codegen_expression(return_value);

    // Assuming the return type is always i32 for simplicity
    printf("  ret i32 %%%d\n", return_value_tmp);

    return temporary;
}

int codegen_le(struct node *le_node) {
    int e1 = codegen_expression(getchild(le_node, 0));
    int e2 = codegen_expression(getchild(le_node, 1));
    printf("  %%%d = icmp sle i32 %%%d, %%%d\n", temporary, e1, e2);
    return temporary++;
}

int codegen_gt(struct node *gt_node) {
    int e1 = codegen_expression(getchild(gt_node, 0));
    int e2 = codegen_expression(getchild(gt_node, 1));
    printf("  %%%d = icmp sgt i32 %%%d, %%%d\n", temporary, e1, e2);
    return temporary++;
}

int codegen_lt(struct node *lt_node) {
    int e1 = codegen_expression(getchild(lt_node, 0));
    int e2 = codegen_expression(getchild(lt_node, 1));
    printf("  %%%d = icmp slt i32 %%%d, %%%d\n", temporary, e1, e2);
    return temporary++;
}

int codegen_ge(struct node *ge_node) {
    int e1 = codegen_expression(getchild(ge_node, 0));
    int e2 = codegen_expression(getchild(ge_node, 1));
    printf("  %%%d = icmp sge i32 %%%d, %%%d\n", temporary, e1, e2);
    return temporary++;
}

int codegen_bitwise_and(struct node *and_node) {
    int e1 = codegen_expression(getchild(and_node, 0));
    int e2 = codegen_expression(getchild(and_node, 1));
    printf("  %%%d = and i32 %%%d, %%%d\n", temporary, e1, e2);
    return temporary++;
}

int codegen_bitwise_xor(struct node *xor_node) {
    int e1 = codegen_expression(getchild(xor_node, 0));
    int e2 = codegen_expression(getchild(xor_node, 1));
    printf("  %%%d = xor i32 %%%d, %%%d\n", temporary, e1, e2);
    return temporary++;
}

int codegen_bitwise_or(struct node *or_node) {
    int e1 = codegen_expression(getchild(or_node, 0));
    int e2 = codegen_expression(getchild(or_node, 1));
    printf("  %%%d = or i32 %%%d, %%%d\n", temporary, e1, e2);
    return temporary++;
}

int codegen_ne(struct node *ne_node) {
    int e1 = codegen_expression(getchild(ne_node, 0));
    int e2 = codegen_expression(getchild(ne_node, 1));
    printf("  %%%d = icmp ne i32 %%%d, %%%d\n", temporary, e1, e2);
    return temporary++;
}

int codegen_eq(struct node *eq_node) {
    int e1 = codegen_expression(getchild(eq_node, 0));
    int e2 = codegen_expression(getchild(eq_node, 1));
    printf("  %%%d = icmp eq i32 %%%d, %%%d\n", temporary, e1, e2);
    return temporary++;
}

int codegen_minus(struct node *minus) {
    int e1 = codegen_expression(getchild(minus, 0));
    printf("  %%%d = sub i32 0, %%%d\n", temporary, e1);

    return temporary++;
}

int codegen_plus(struct node *plus_node) {
    int e1 = codegen_expression(getchild(plus_node, 0));
    printf("  %%%d = add i32 0, %%%d\n", temporary, e1);
    return temporary++;
}

int codegen_not(struct node *not_node) {
    int e1 = codegen_expression(getchild(not_node, 0));
    printf("  %%%d = icmp eq i32 %%%d, 0\n", temporary, e1);
    return temporary++;
}

int codegen_store(struct node *store_node) {
    struct node *target = getchild(store_node, 0);
    struct node *value = getchild(store_node, 1);

    int value_tmp = codegen_expression(value);

    if (search_symbol(symbol_table, target->token)) // Variavel global
        printf("  store i32 %%%d, i32* @%s\n", value_tmp, target->token);
    else
        printf("  store i32 %%%d, i32* %%_%s\n", value_tmp, target->token);

    return temporary;
}

int codegen_chrlit(struct node *chrlit_node) {

    char char_value = get_value(chrlit_node->token);

    printf("  %%%d = add i32 %d, 0\n", temporary, char_value);

    return temporary++;
}

void codegen_Statlist(struct node *expression) {
    struct node_list *children = expression->children;

    while ((children = children->next) != NULL) {
        codegen_expression(children->node);
    }
}

int codegen_expression(struct node *expression) {
    char *category_array[43] = {"Program", "Declaration", "FuncDeclaration", "FuncDefinition", "ParamList", "FuncBody", "ParamDeclaration", "StatList", "If", "While", "Return", "Or", "And", "Eq", "Ne", "Lt", "Gt", "Le", "Ge", "Add", "Sub", "Mul", "Div", "Mod", "Not", "Minus", "Plus", "Store", "Comma", "Call", "BitWiseAnd", "BitWiseXor", "BitWiseOr", "Char", "ChrLit", "Identifier", "Int", "Short", "Natural", "Double", "Decimal", "Void", "Null"};
    int tmp = -1;
    switch (expression->category) {
    case Identifier:
        tmp = codegen_identifier(expression);
        break;
    case Natural:
        tmp = codegen_natural(expression);
        break;
    case Decimal:
        tmp = codegen_decimal(expression);
        break;
    case ChrLit:
        tmp = codegen_chrlit(expression);
        break;
    case Call:
        tmp = codegen_call(expression);
        break;
    case If:
        tmp = codegen_ifthenelse(expression);
        break;
    case Add:
        tmp = codegen_add(expression);
        break;
    case Sub:
        tmp = codegen_sub(expression);
        break;
    case Mul:
        tmp = codegen_mul(expression);
        break;
    case Div:
        tmp = codegen_div(expression);
        break;
    case While:
        tmp = codegen_while(expression);
        break;
    case Declaration:
        tmp = codegen_declaration(expression);
        break;
    case Return:
        tmp = codegen_return(expression);
        break;
    case StatList:
        codegen_Statlist(expression);
        break;
    case Le:
        tmp = codegen_le(expression);
        break;
    case Lt:
        tmp = codegen_lt(expression);
        break;
    case Gt:
        tmp = codegen_gt(expression);
        break;
    case Ge:
        tmp = codegen_ge(expression);
        break;
    case BitWiseAnd:
        tmp = codegen_bitwise_and(expression);
        break;
    case BitWiseOr:
        tmp = codegen_bitwise_or(expression);
        break;
    case BitWiseXor:
        tmp = codegen_bitwise_xor(expression);
        break;
    case Store:
        tmp = codegen_store(expression);
        break;
    case Minus:
        tmp = codegen_minus(expression);
        break;
    case Eq:
        tmp = codegen_eq(expression);
        break;
    case Ne:
        tmp = codegen_ne(expression);
        break;
    case Not:
        tmp = codegen_not(expression);
        break;
    case Plus:
        tmp = codegen_plus(expression);
        break;
    default:
        if (expression->category != Null)
            printf("\n-->%s\n", category_array[expression->category]);
        break;
    }
    return tmp;
}

int codegen_funcbody(struct node *funcbody) {
    struct node_list *children = funcbody->children;

    while ((children = children->next) != NULL) {
        codegen_expression(children->node);
        if (children->node->category == Return)
            return 1;
    }

    return 0;
}

void codegen_parameters(struct node *parameters) {
    // char* category_array[43] = {"Program", "Declaration", "FuncDeclaration", "FuncDefinition", "ParamList", "FuncBody", "ParamDeclaration", "StatList", "If", "While", "Return", "Or", "And", "Eq", "Ne", "Lt", "Gt", "Le", "Ge", "Add", "Sub", "Mul", "Div", "Mod", "Not", "Minus", "Plus", "Store", "Comma", "Call", "BitWiseAnd", "BitWiseXor", "BitWiseOr", "Char", "ChrLit", "Identifier", "Int", "Short", "Natural", "Double", "Decimal", "Void", "Null" };
    struct node *parameter;
    int curr = 0;
    while ((parameter = getchild(parameters, curr++)) != NULL) {
        if (getchild(parameter, 0)->category != Void) {
            if (curr > 1)
                printf(", ");
            if (getchild(parameter, 1))
                printf("i32 %%%s", getchild(parameter, 1)->token);
            else
                printf("i32");
        }
    }

    printf(") {\n");

    curr = 0;

    while ((parameter = getchild(parameters, curr++)) != NULL) {
        if (getchild(parameter, 0)->category != Void) {
            // Map UC data types to LLVM IR types
            const char *llvm_type;
            if (getchild(parameter, 0)->category == Int || getchild(parameter, 0)->category == Short || getchild(parameter, 0)->category == Char) {
                llvm_type = "i32";
            } else if (getchild(parameter, 0)->category == Double) {
                llvm_type = "double";
            }

            // Code generation for initializing with a constant value (if provided)

            // Code generation for variable declaration
            printf("  %%_%s = alloca %s\n", getchild(parameter, 1)->token, llvm_type);

            printf("  store %s %%%s, %s* %%_%s\n", llvm_type, getchild(parameter, 1)->token, llvm_type, getchild(parameter, 1)->token);
        }
    }
}

void codegen_function(struct node *function) {
    // char* category_array[43] = {"Program", "Declaration", "FuncDeclaration", "FuncDefinition", "ParamList", "FuncBody", "ParamDeclaration", "StatList", "If", "While", "Return", "Or", "And", "Eq", "Ne", "Lt", "Gt", "Le", "Ge", "Add", "Sub", "Mul", "Div", "Mod", "Not", "Minus", "Plus", "Store", "Comma", "Call", "BitWiseAnd", "BitWiseXor", "BitWiseOr", "Char", "ChrLit", "Identifier", "Int", "Short", "Natural", "Double", "Decimal", "Void", "Null" };
    // printf("%s\n", category_array[function])
    int flag = 0;
    temporary = 1;
    if (getchild(function, 0)->category == Int || getchild(function, 0)->category == Short || getchild(function, 0)->category == Char)
        printf("define i32 @_%s(", getchild(function, 1)->token);
    if (getchild(function, 0)->category == Double)
        printf("define double @_%s(", getchild(function, 1)->token);
    if (getchild(function, 0)->category == Void)
        printf("define void @_%s(", getchild(function, 1)->token);

    codegen_parameters(getchild(function, 2));
    flag = codegen_funcbody(getchild(function, 3));
    if (!flag) {
        if (getchild(function, 0)->category == Int || getchild(function, 0)->category == Short || getchild(function, 0)->category == Char)
            printf("  ret i32 1\n");
        if (getchild(function, 0)->category == Double)
            printf("  ret double 1\n");
        if (getchild(function, 0)->category == Void)
            printf("  ret void\n");
    }
    printf("}\n\n");
}

void codegen_func_dec(struct node *func_dec) {
    printf("Func_dec\n");
}

void codegen_global_aux(struct node *declaration) {
    struct node *type_node = getchild(declaration, 0);
    struct node *identifier_node = getchild(declaration, 1);
    struct node *value_node = getchild(declaration, 2);

    // Map UC data types to LLVM IR types
    const char *llvm_type;
    if (type_node->category == Int || type_node->category == Short || type_node->category == Char) {
        llvm_type = "i32";
    } else if (type_node->category == Double) {
        llvm_type = "double";
    }

    if (value_node != NULL) {
        int teste = codegen_expression(value_node);

        printf("  store %s %%%d, %s* @%s\n", llvm_type, teste, llvm_type, identifier_node->token);
    }
}

void codegen_global_dec(struct node *declaration) {
    struct node *type_node = getchild(declaration, 0);
    struct node *identifier_node = getchild(declaration, 1);
    struct node *value_node = getchild(declaration, 2);

    // Map UC data types to LLVM IR types
    const char *llvm_type;
    if (type_node->category == Int || type_node->category == Short || type_node->category == Char) {
        llvm_type = "i32";
    } else if (type_node->category == Double) {
        llvm_type = "double";
    }

    if (value_node != NULL) {
        if (type_node->category == Double)
            printf("@%s = global %s 0.0\n", identifier_node->token, llvm_type);
        else
            printf("@%s = global %s 0\n", identifier_node->token, llvm_type);
    }
}

// code generation begins here, with the AST root node
void codegen_program(struct node *program) {
    // char* category_array[43] = {"Program", "Declaration", "FuncDeclaration", "FuncDefinition", "ParamList", "FuncBody", "ParamDeclaration", "StatList", "If", "While", "Return", "Or", "And", "Eq", "Ne", "Lt", "Gt", "Le", "Ge", "Add", "Sub", "Mul", "Div", "Mod", "Not", "Minus", "Plus", "Store", "Comma", "Call", "BitWiseAnd", "BitWiseXor", "BitWiseOr", "Char", "ChrLit", "Identifier", "Int", "Short", "Natural", "Double", "Decimal", "Void", "Null" };

    // predeclared functions
    printf("declare i32 @getchar()\n");
    printf("declare i32 @putchar(i32)\n");

    // generate the code for each function
    struct node_list *function = program->children;
    while ((function = function->next) != NULL) {
        if (function->node->category == FuncDefinition)
            codegen_function(function->node);
        else if (function->node->category == FuncDeclaration)
            codegen_func_dec(function->node);
        else if (function->node->category == Declaration)
            codegen_global_dec(function->node);
    }

    // generate the entry point which calls main(integer) if it exists
    struct symbol_list *entry = search_symbol(symbol_table, "main");
    temporary = 1;
    if (entry != NULL && entry->node->category == FuncDefinition) {
        printf("define i32 @main() {\n");

        function = program->children;
        while ((function = function->next) != NULL) {
            if (function->node->category == Declaration)
                codegen_global_aux(function->node);
        }

        printf("  %%%d = call i32 @_main()\n", temporary);
        printf("  ret i32 %%1\n"
               "}\n");
    }
}