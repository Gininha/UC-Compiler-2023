#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "semantics.h"

//extern int has_error;
int *num_params, *num_args;
struct symbol_list *symbol_table;

struct symbol_list* search_table(struct list_symbol_list* list, char* name){
    struct list_symbol_list *aux = list;

    while(aux->next != NULL){
        if(strcmp(name, aux->name) == 0){
            return aux->list;
        }
        aux = aux->next;
    }

    return NULL;
}

bool check_equal(struct node_list *arguments, struct param_list *params, struct symbol_list *table){
    //char* category_array[43] = {"Program", "Declaration", "FuncDeclaration", "FuncDefinition", "ParamList", "FuncBody", "ParamDeclaration", "StatList", "If", "While", "Return", "Or", "And", "Eq", "Ne", "Lt", "Gt", "Le", "Ge", "Add", "Sub", "Mul", "Div", "Mod", "Not", "Minus", "Plus", "Store", "Comma", "Call", "BitWiseAnd", "BitWiseXor", "BitWiseOr", "Char", "ChrLit", "Identifier", "Int", "Short", "Natural", "Double", "Decimal", "Void", "Null" };
    *num_params = 0;
    *num_args = 0;
    
    while(params && arguments){
        check_expression(arguments->node, table);
        if(params->type != arguments->node->type){
            if(arguments->node->category == Call){
                if(getchild(arguments->node, 0)->category == Identifier)
                    if(!((arguments->node->type == char_type || params->type == char_type) && (arguments->node->type == integer_type || params->type == integer_type)))
                        printf("Line %d, column %d: Conflicting types (got %s, expected %s)\n", getchild(arguments->node, 0)->line, getchild(arguments->node, 0)->column, type_name(arguments->node->type), type_name(params->type));
            }else{
                if(arguments->node->category == Identifier)
                    if(!((arguments->node->type == char_type || params->type == char_type) && (arguments->node->type == integer_type || params->type == integer_type)))
                        printf("Line %d, column %d: Conflicting types (got %s, expected %s)\n", arguments->node->line, arguments->node->column, type_name(arguments->node->type), type_name(params->type));
            }//printf("%s\n", category_array[arguments->node->category]);
        }
        (*num_params)++;
        (*num_args)++;
        params = params->next;
        arguments = arguments->next;
    }
    
    while(params){
        (*num_params)++;
        params = params->next;
    }

    while(arguments){
        (*num_args)++;
        check_expression(arguments->node, table);
        arguments = arguments->next;
    }

    if((*num_args) != (*num_params))
        return false;
    return true;
}

void check_expression(struct node *expression, struct symbol_list *table){
    //char* category_array[43] = {"Program", "Declaration", "FuncDeclaration", "FuncDefinition", "ParamList", "FuncBody", "ParamDeclaration", "StatList", "If", "While", "Return", "Or", "And", "Eq", "Ne", "Lt", "Gt", "Le", "Ge", "Add", "Sub", "Mul", "Div", "Mod", "Not", "Minus", "Plus", "Store", "Comma", "Call", "BitWiseAnd", "BitWiseXor", "BitWiseOr", "Char", "ChrLit", "Identifier", "Int", "Short", "Natural", "Double", "Decimal", "Void", "Null" };
    //printf("%s\n", category_name[expression->category]);
    
    struct symbol_list* aux, *aux2;
    struct node_list *children = expression->children;

    switch(expression->category){

        case Identifier:
            if(((aux = search_symbol(table, expression->token)) == NULL) && ((aux2 = search_symbol(symbol_table, expression->token)) == NULL)) {
                printf("Line %d, column %d: Unknown symbol %s\n", expression->line, expression->column, expression->token);
                expression->type = undef_type;
                //has_error = 1;
            }else{
                if(aux){
                    expression->type = aux->type;
                }
                else{
                    expression->type = aux2->type;
                }
            }
            break;
        case Natural:
            expression->type = integer_type;
            break;
        case Decimal:
            expression->type = double_type;
            break;
        case ChrLit:
            expression->type = integer_type;
            break;
        case StatList:
            while((children = children->next) != NULL){
                check_expression(children->node, table);
            }
            break;
        case Call:
            if(search_symbol(symbol_table, getchild(expression, 0)->token) == NULL) {
                printf("Function %s undeclared\n", getchild(expression, 0)->token);
                //has_error = 1;
            }else{
                
                struct node_list *arguments = expression->children->next->next;
                struct param_list *params = search_symbol(symbol_table, getchild(expression, 0)->token)->params_list;
                //printf("%s %s\n", category_array[getchild(expression, 0)->category], getchild(expression, 0)->token);
                
                getchild(expression, 0)->type = search_symbol(symbol_table, getchild(expression, 0)->token)->type;
                getchild(expression, 0)->params_list = search_symbol(symbol_table, getchild(expression, 0)->token)->params_list;
                expression->type = search_symbol(symbol_table, getchild(expression, 0)->token)->type;

                if(check_equal(arguments, params, table)){

                }else{
                    printf("Line %d, column %d: Wrong number of arguments to function %s (got %d, required %d)\n", getchild(expression, 0)->line, getchild(expression, 0)->column, getchild(expression, 0)->token, *num_args, *num_params);
                    //Numero errado
                }
            }
            break;
        case If:
            check_expression(getchild(expression, 0), table);
            check_expression(getchild(expression, 1), table);
            check_expression(getchild(expression, 2), table);
            if(getchild(expression, 0)->type != integer_type){
                printf("Line %d, column %d: Conflicting types (got %s, expected int)\n", getchild(expression, 0)->line, getchild(expression, 0)->column, type_name(getchild(expression, 0)->type));
            }
            break;
        case Comma:
            check_expression(getchild(expression, 0), table);
            check_expression(getchild(expression, 1), table);

            if(getchild(expression, 0)->type >= getchild(expression, 1)->type)
                expression->type = getchild(expression, 0)->type;
            else
                expression->type = getchild(expression, 1)->type;

            break;
        case Store:
            check_expression(getchild(expression, 0), table);
            check_expression(getchild(expression, 1), table);

            if(getchild(expression, 0)->type == undef_type || getchild(expression, 1)->type == undef_type)
                printf("Line %d, column %d: Operator = cannot be applied to types %s, %s\n", expression->line, expression->column, type_name(getchild(expression, 0)->type), type_name(getchild(expression, 1)->type));
            else{
                if(getchild(expression, 1)->type == double_type){
                    if(getchild(expression, 1)->type > getchild(expression, 0)->type)
                        printf("Line %d, column %d: Operator = cannot be applied to types %s, %s\n", expression->line, expression->column, type_name(getchild(expression, 0)->type), type_name(getchild(expression, 1)->type));
                }
            }
        
            if(getchild(expression, 0)->category != Identifier){
                printf("Line %d, column %d: Lvalue required\n", getchild(expression, 0)->line, getchild(expression, 0)->column);
                //has_error = 1;
            }

            enum type type1 = getchild(expression, 0)->type;
            expression->type = type1;
            break;
        case Add:
        case Sub:
        case Mul:
        case Div:
            check_expression(getchild(expression, 0), table);
            check_expression(getchild(expression, 1), table);

            if(getchild(expression, 0)->type == undef_type && getchild(expression, 1)->type == undef_type){
                expression->type = undef_type;
                printf("Line %d, column %d: Operator %s cannot be applied to types undef, undef\n", expression->line, expression->column, symbol_type(expression->category));
            }
            else{
                if(getchild(expression, 0)->type == void_type || getchild(expression, 1)->type == void_type){
                    expression->type = undef_type;
                    printf("Line %d, column %d: Operator %s cannot be applied to types %s, %s\n", expression->line, expression->column, symbol_type(expression->category), type_name(getchild(expression, 0)->type), type_name(getchild(expression, 1)->type));
                }else{
                    if(getchild(expression, 0)->type >= getchild(expression, 1)->type)
                        expression->type = getchild(expression, 0)->type;
                    else
                        expression->type = getchild(expression, 1)->type;
                }
            }
            break;
        case Or:
        case And:
        case Mod:
        case BitWiseAnd:
        case BitWiseOr:
        case BitWiseXor:

            check_expression(getchild(expression, 0), table);
            check_expression(getchild(expression, 1), table);
            expression->type = integer_type;

            if (getchild(expression, 0)->type == double_type || getchild(expression, 1)->type == double_type || getchild(expression, 0)->type == undef_type || getchild(expression, 1)->type == undef_type) {
                printf("Line %d, column %d: Operator %s cannot be applied to types %s, %s\n", expression->line, expression->column, symbol_type(expression->category), type_name(getchild(expression, 0)->type), type_name(getchild(expression, 1)->type));
            }
            
            break;
        case Eq:
        case Ne:
        case Le:
        case Ge:
        case Lt:
        case Gt:
            check_expression(getchild(expression, 0), table);
            check_expression(getchild(expression, 1), table);
            expression->type = integer_type;

            if(getchild(expression, 0)->type == undef_type || getchild(expression, 1)->type == undef_type){
                printf("Line %d, column %d: Operator %s cannot be applied to types %s, %s\n", expression->line, expression->column, symbol_type(expression->category), type_name(getchild(expression, 0)->type), type_name(getchild(expression, 1)->type));
            }

            break;
        case Plus:
        case Minus:
            check_expression(getchild(expression, 0), table);
            if(getchild(expression, 0)->type == void_type){
                printf("Line %d, column %d: Operator %s cannot be applied to type void\n", expression->line, expression->column, symbol_type(expression->category));
            }
            expression->type = getchild(expression, 0)->type;
            break;
        case Not:
            check_expression(getchild(expression, 0), table);
            expression->type = integer_type;
            
            break;
        default:
            break;
    }
}

struct symbol_list * add_to_list_of_tables(struct list_symbol_list * lista, char *name){
    struct symbol_list *new_table = (struct symbol_list *) malloc(sizeof(struct symbol_list));
    new_table->next = NULL;
    struct list_symbol_list * aux = lista;
                
    while(aux->next != NULL){
        aux = aux->next;
    }
    aux->list = new_table;
    aux->name = name;
    aux->next = (struct list_symbol_list *) malloc(sizeof(struct list_symbol_list));
    aux->next->next = NULL;

    return new_table;
}

void add_to_params_list(struct symbol_list *func, enum type type){
    struct param_list *aux = func->params_list;
    if (aux) {
        while (aux->next != NULL) {
            aux = aux->next;
        }
            aux->next = (struct param_list *)malloc(sizeof(struct param_list));
            aux = aux->next;
            aux->type = type;
            aux->next = NULL;
        } else {
            func->params_list = (struct param_list *)malloc(sizeof(struct param_list));
            func->params_list->type = type;
            func->params_list->next = NULL;
        }
}

void check_ParamList(struct node* ParamList, struct symbol_list *table, struct symbol_list *func){
    
    struct node_list *children = ParamList->children;
    int flag = 0;

    if(func->params_list == NULL)
        flag = 1;

    while((children = children->next) != NULL){
        enum type type = category_type(getchild(children->node, 0)->category);
        struct node *id;
        if((id = getchild(children->node, 1)) != NULL){
            if(search_symbol(table, id->token) == NULL) {
                insert_symbol(table, id->token, type, id, 1);
                if(flag)
                    add_to_params_list(func, type);
            } else {
                //printf("Identifier %s (%d:%d) already declared\n", id->token, id->token_line, id->token_column);
                //has_error = 1;
            }
        }else{
            add_to_params_list(func, type);
        }
    }

}

void check_funcbody(struct node* funcbody, struct symbol_list *table, enum type tipo){

    struct node_list *children = funcbody->children;
    struct node_list *child;

    while((children = children->next) != NULL){
        switch(children->node->category){
            case Declaration:
                check_declaration(children->node, table);
                break;
            case Return:
                check_expression(getchild(children->node, 0), table);
                if(getchild(children->node, 0)->type != tipo)
                    printf("Line %d, column %d: Conflicting types (got %s, expected %s)\n", getchild(children->node, 0)->line, getchild(children->node, 0)->column, type_name(getchild(children->node, 0)->type), type_name(tipo));
                break;
            case While:
                child = children->node->children;
                while((child = child->next) != NULL){
                    check_expression(child->node, table);
                }
                break;
            case If:
                check_expression(children->node, table);
                break;
            case StatList:
                check_expression(children->node, table);
                break;                
            default:
                check_expression(children->node, table);
        }
    }

}

void check_function(struct node *function, struct symbol_list *table) {
    //char* category_array[43] = {"Program", "Declaration", "FuncDeclaration", "FuncDefinition", "ParamList", "FuncBody", "ParamDeclaration", "StatList", "If", "While", "Return", "Or", "And", "Eq", "Ne", "Lt", "Gt", "Le", "Ge", "Add", "Sub", "Mul", "Div", "Mod", "Not", "Minus", "Plus", "Store", "Comma", "Call", "BitWiseAnd", "BitWiseXor", "BitWiseOr", "Char", "ChrLit", "Identifier", "Int", "Short", "Natural", "Double", "Decimal", "Void", "Null" };

    //printf("func\n");
    insert_symbol(symbol_table, getchild(function, 1)->token, category_type(getchild(function, 0)->category), function, 0);
    insert_symbol(table, "return", category_type(getchild(function, 0)->category), getchild(function, 1), 0);
    check_ParamList(getchild(function, 2), table, search_symbol(symbol_table, getchild(function, 1)->token));
    check_funcbody(getchild(function, 3), table, category_type(getchild(function, 0)->category));
    
}

void check_declaration(struct node *declaration, struct symbol_list *table){
    //printf("dec\n");
    enum type type = category_type(getchild(declaration, 0)->category);
    struct node *id = getchild(declaration, 1);
    int i = 2;

    if(id->category == Identifier){
        if(search_symbol(table, id->token) == NULL) {
            insert_symbol(table, id->token, type, id, 0);
        } else {
            //printf("Identifier %s (%d:%d) already declared\n", id->token, id->token_line, id->token_column);
            //has_error = 1;
        }
    }

    while((id = getchild(declaration, i)) != NULL){
        if(id->category == Identifier){
            if(search_symbol(table, id->token) == NULL && id->category == Identifier) {
                id->type = undef_type;
            }
        }
        check_expression(id, table);
        i++;
    }


}

void check_funcdeclatarion(struct node *func_dec, struct list_symbol_list * lista){
    //printf("func_dec\n");
    //char* category_array[43] = {"Program", "Declaration", "FuncDeclaration", "FuncDefinition", "ParamList", "FuncBody", "ParamDeclaration", "StatList", "If", "While", "Return", "Or", "And", "Eq", "Ne", "Lt", "Gt", "Le", "Ge", "Add", "Sub", "Mul", "Div", "Mod", "Not", "Minus", "Plus", "Store", "Comma", "Call", "BitWiseAnd", "BitWiseXor", "BitWiseOr", "Char", "ChrLit", "Identifier", "Int", "Short", "Natural", "Double", "Decimal", "Void", "Null" };
    enum type type = category_type(getchild(func_dec, 0)->category);
    struct node *id = getchild(func_dec, 1);
    int flag = 1;

    if(search_symbol(symbol_table, id->token) == NULL) {
        struct node_list *ParamList = getchild(func_dec, 2)->children;
        while((ParamList = ParamList->next) != NULL){
            if(getchild(ParamList->node, 0)->category == Void){
                flag = 0;
                printf("Line %d, column %d: Invalid use of void type in declaration\n", getchild(ParamList->node, 0)->line, getchild(ParamList->node, 0)->column);
            }
        }

        if(flag){
            insert_symbol(symbol_table, id->token, type, id, 0);
            check_ParamList(getchild(func_dec, 2), NULL, search_symbol(symbol_table, id->token));

        }
    } else {
        //printf("Identifier %s (%d:%d) already declared\n", id->token, id->token_line, id->token_column);
        //has_error = 1;
    }
}

// semantic analysis begins here, with the AST root node
void check_program(struct node *program) {
    //char* category_array[43] = {"Program", "Declaration", "FuncDeclaration", "FuncDefinition", "ParamList", "FuncBody", "ParamDeclaration", "StatList", "If", "While", "Return", "Or", "And", "Eq", "Ne", "Lt", "Gt", "Le", "Ge", "Add", "Sub", "Mul", "Div", "Mod", "Not", "Minus", "Plus", "Store", "Comma", "Call", "BitWiseAnd", "BitWiseXor", "BitWiseOr", "Char", "ChrLit", "Identifier", "Int", "Short", "Natural", "Double", "Decimal", "Void", "Null" };

    symbol_table = (struct symbol_list *) malloc(sizeof(struct symbol_list));
    symbol_table->next = NULL;

    struct list_symbol_list * lista = (struct list_symbol_list *) malloc(sizeof(struct list_symbol_list));
    lista->next = NULL;

    num_args = (int *) malloc(sizeof(int));
    num_params = (int *) malloc(sizeof(int));

    insert_symbol(symbol_table, "putchar", category_type(Int), newnode(FuncDeclaration, NULL), 0);
    add_to_params_list(search_symbol(symbol_table, "putchar"), category_type(Int));
    insert_symbol(symbol_table, "getchar", category_type(Int), newnode(FuncDeclaration, NULL), 0);
    add_to_params_list(search_symbol(symbol_table, "getchar"), category_type(Void));

    struct symbol_list *new_table;
    struct node_list *child = program->children;
    while((child = child->next) != NULL){

        switch(child->node->category){
            
            case Declaration:

                check_declaration(child->node, symbol_table);
                break;

            case FuncDefinition:

                if(search_table(lista, getchild(child->node, 1)->token) == NULL){
                    new_table = add_to_list_of_tables(lista, getchild(child->node, 1)->token);
                    check_function(child->node, new_table);
                }else{
                    printf("Line %d, column %d: Symbol %s already defined\n", getchild(child->node, 1)->line, getchild(child->node, 1)->column, getchild(child->node, 1)->token);
                }
                break;

            case FuncDeclaration:

                check_funcdeclatarion(child->node, lista);

                break;

            default:
                break;
        }
        
    }
    printf("===== Global Symbol Table =====\n");
    show_symbol_table(symbol_table);
    printf("\n");
    struct list_symbol_list * aux = lista;
                
    while(aux->next != NULL){
        printf("===== Function %s Symbol Table =====\n", aux->name);
        show_symbol_table(aux->list);
        printf("\n");
        aux = aux->next;
    }

}

// insert a new symbol in the list, unless it is already there
struct symbol_list *insert_symbol(struct symbol_list *table, char *identifier, enum type type, struct node *node, int is_param) {
    struct symbol_list *new = (struct symbol_list *) malloc(sizeof(struct symbol_list));
    new->identifier = strdup(identifier);
    new->type = type;
    if(is_param)
        new->param = true;
    else
        new->param = false;
    new->node = node;
    new->params_list = NULL;
    new->next = NULL;
    struct symbol_list *symbol = table;
    while(symbol != NULL) {
        if(symbol->next == NULL) {
            symbol->next = new;    /* insert new symbol at the tail of the list */
            break;
        } else if(strcmp(symbol->next->identifier, identifier) == 0) {
            free(new);
            return NULL;           /* return NULL if symbol is already inserted */
        }
        symbol = symbol->next;
    }
    return new;
}

// look up a symbol by its identifier
struct symbol_list *search_symbol(struct symbol_list *table, char *identifier) {
    struct symbol_list *symbol;
    if(table){    
        for(symbol = table->next; symbol != NULL; symbol = symbol->next)
            if(strcmp(symbol->identifier, identifier) == 0)
                return symbol;
        return NULL;
    }
    return NULL;
}

void show_symbol_table(struct symbol_list *table) {
    struct symbol_list *symbol;
    //char* type_array[4] = {"int", "double", "char", "short", "no_type"};
    for(symbol = table->next; symbol != NULL; symbol = symbol->next){
        printf("%s\t%s", symbol->identifier, type_name(symbol->type));
        if(symbol->params_list){
            printf("(");
            struct param_list *aux = symbol->params_list;
            while(aux){
                if(aux->next)
                    printf("%s,", type_name(aux->type));
                else
                    printf("%s", type_name(aux->type));
                aux = aux->next;
            }
            printf(")");
        }
        if(symbol->param)
            printf("\tparam");
        printf("\n");
    }
}
