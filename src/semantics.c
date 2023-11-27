#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "semantics.h"

//extern int has_error;

struct symbol_list *symbol_table;


bool check_equal(struct node_list *arguments, struct param_list *params){
    int num = 0;

    while(params){
        num++;
        params = params->next;
    }

    while(arguments){
        num--;
        arguments = arguments->next;
    }

    if(num)
        return false;
    return true;
}

void check_expression(struct node *expression, struct symbol_list *table){
    //char* category_array[43] = {"Program", "Declaration", "FuncDeclaration", "FuncDefinition", "ParamList", "FuncBody", "ParamDeclaration", "StatList", "If", "While", "Return", "Or", "And", "Eq", "Ne", "Lt", "Gt", "Le", "Ge", "Add", "Sub", "Mul", "Div", "Mod", "Not", "Minus", "Plus", "Store", "Comma", "Call", "BitWiseAnd", "BitWiseXor", "BitWiseOr", "Char", "ChrLit", "Identifier", "Int", "Short", "Natural", "Double", "Decimal", "Void", "Null" };
    //printf("%s\n", category_name[expression->category]);
    
    struct symbol_list* aux, *aux2;

    switch(expression->category){

        case Identifier:
            if(((aux = search_symbol(table, expression->token)) == NULL) && ((aux2 = search_symbol(symbol_table, expression->token)) == NULL)) {
                printf("Symbol %s undeclared\n", expression->token);
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
            printf("dec\n");
            break;
        case ChrLit:
            expression->type = integer_type;
            break;
        case StatList:
            struct node_list *children = expression->children;
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
                
                if(check_equal(arguments, params)){
                    while(arguments){
                        check_expression(arguments->node, table);
                        arguments = arguments->next;
                    }
                    getchild(expression, 0)->type = search_symbol(symbol_table, getchild(expression, 0)->token)->type;
                    getchild(expression, 0)->params_list = search_symbol(symbol_table, getchild(expression, 0)->token)->params_list;
                    expression->type = search_symbol(symbol_table, getchild(expression, 0)->token)->type;
                }else{
                    //Numero errado
                }
            }
            break;
        case If:
            check_expression(getchild(expression, 0), table);
            check_expression(getchild(expression, 1), table);
            check_expression(getchild(expression, 2), table);
            break;
        case Comma:
        case Store:
        case Add:
        case Sub:
        case Mul:
        case Div:
        case Mod:
        case Or:
        case And:
        case BitWiseAnd:
        case BitWiseOr:
        case BitWiseXor:
        case Eq:
        case Ne:
        case Le:
        case Ge:
        case Lt:
        case Gt:
            check_expression(getchild(expression, 0), table);
            check_expression(getchild(expression, 1), table);

            enum type type1 = getchild(expression, 0)->type;
            enum type type2 = getchild(expression, 1)->type;

            if(type1 == type2){
                //printf("%s - %s\n", category_array[expression->category], type_name(expression->type));
                expression->type = type1;
            }else{
                //erro? maybe? idk!
            }
            break;
        case Plus:
        case Minus:
        case Not:
            check_expression(getchild(expression, 0), table);
            break;
        default:
            break;
    }
}

/*
void check_parameters(struct node *parameter){
    //char *category_name[] = names;
    struct node_list *parameters = parameter->children;

    while((parameters = parameters->next) != NULL){
        struct node *id = getchild(parameters->node, 1);
        //printf("%s\n", category_name[id->category]);
        enum type type = category_type(getchild(parameters->node, 0)->category);
        //printf("%d\n", type);
        if(search_symbol(symbol_table, id->token) == NULL) {
            insert_symbol(symbol_table, id->token, type, parameters->node);
        } else {
            printf("Identifier %s (%d:%d) already declared\n", id->token, id->token_line, id->token_column);
            has_error = 1;
        }
    }
    
}
*/

struct symbol_list * add_to_list_of_tables(struct list_symbol_list * lista, struct node_list *child){
    struct symbol_list *new_table = (struct symbol_list *) malloc(sizeof(struct symbol_list));
    new_table->next = NULL;
    struct list_symbol_list * aux = lista;
                
    while(aux->next != NULL){
        aux = aux->next;
    }
    aux->list = new_table;
    aux->name = getchild(child->node, 1)->token;
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

    while((children = children->next) != NULL){
        enum type type = category_type(getchild(children->node, 0)->category);
        struct node *id;
        if((id = getchild(children->node, 1)) != NULL){
            if(search_symbol(table, id->token) == NULL) {
                insert_symbol(table, id->token, type, id, 1);
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

void check_funcbody(struct node* funcbody, struct symbol_list *table){

    struct node_list *children = funcbody->children;

    while((children = children->next) != NULL){
        switch(children->node->category){
            case Declaration:
                check_declaration(children->node, table);
                break;
            case Return:
                check_expression(getchild(children->node, 0), table);
                break;
            case While:
                struct node_list *child = children->node->children;
                while((child = child->next) != NULL){
                    check_expression(child->node, table);
                }
                break;
            case If:
                check_expression(children->node, table);
                break;
            case StatList:
                break;                
            default:
                
        }
    }

}

void check_function(struct node *function, struct symbol_list *table) {
    //char* category_array[43] = {"Program", "Declaration", "FuncDeclaration", "FuncDefinition", "ParamList", "FuncBody", "ParamDeclaration", "StatList", "If", "While", "Return", "Or", "And", "Eq", "Ne", "Lt", "Gt", "Le", "Ge", "Add", "Sub", "Mul", "Div", "Mod", "Not", "Minus", "Plus", "Store", "Comma", "Call", "BitWiseAnd", "BitWiseXor", "BitWiseOr", "Char", "ChrLit", "Identifier", "Int", "Short", "Natural", "Double", "Decimal", "Void", "Null" };

    //printf("func\n");
    if(search_symbol(symbol_table, getchild(function, 1)->token) == NULL) {
        insert_symbol(symbol_table, getchild(function, 1)->token, category_type(getchild(function, 0)->category), function, 0);
    } else {
        //printf("Identifier %s (%d:%d) already declared\n", id->token, id->token_line, id->token_column);
        //has_error = 1;
    }

    insert_symbol(table, "return", category_type(getchild(function, 0)->category), getchild(function, 1), 0);
    check_ParamList(getchild(function, 2), table, search_symbol(symbol_table, getchild(function, 1)->token));
    check_funcbody(getchild(function, 3), table);
}

void check_declaration(struct node *declaration, struct symbol_list *table){
    //printf("dec\n");
    enum type type = category_type(getchild(declaration, 0)->category);
    struct node *id = getchild(declaration, 1);
    if(search_symbol(table, id->token) == NULL) {
        insert_symbol(table, id->token, type, id, 0);
    } else {
        //printf("Identifier %s (%d:%d) already declared\n", id->token, id->token_line, id->token_column);
        //has_error = 1;
    }


}

void check_funcdeclatarion(struct node *func_dec, struct symbol_list *table){
    //printf("func_dec\n");
    enum type type = category_type(getchild(func_dec, 0)->category);
    struct node *id = getchild(func_dec, 1);

    if(search_symbol(symbol_table, id->token) == NULL) {
        insert_symbol(symbol_table, id->token, type, id, 0);
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

                new_table = add_to_list_of_tables(lista, child);
                check_function(child->node, new_table);
                break;

            case FuncDeclaration:

                check_funcdeclatarion(child->node, NULL);
                break;

            default:

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
    for(symbol = table->next; symbol != NULL; symbol = symbol->next)
        if(strcmp(symbol->identifier, identifier) == 0)
            return symbol;
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
