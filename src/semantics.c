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
                    if(arguments->node->type == double_type || arguments->node->type == void_type || arguments->node->type == undef_type )
                        printf("Line %d, column %d: Conflicting types (got %s, expected %s)\n", getchild(arguments->node, 0)->line, getchild(arguments->node, 0)->column, type_name(arguments->node->type), type_name(params->type));
            }else{
                if(arguments->node->type == double_type || arguments->node->type == void_type || arguments->node->type == undef_type )
                    printf("Line %d, column %d: Conflicting types (got %s, expected %s)\n", arguments->node->line, arguments->node->column, type_name(arguments->node->type), type_name(params->type));
            }//printf("%s\n", category_array[arguments->node->category]);
        }
        if(params->type != void_type)
            (*num_params)++;
        (*num_args)++;
        params = params->next;
        arguments = arguments->next;
    }
    
    while(params){
        if(params->type != void_type)
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

void erros_bueda_estranhos2(struct node* expression){
    struct symbol_list* aux = NULL, *aux2 = NULL;
    struct param_list* aux_p = NULL, *aux2_p = NULL;
    struct param_list* aux_p2 = NULL, *aux2_p2 = NULL;
    int flag_p = 0;

    if(getchild(expression, 0)->category == Identifier || getchild(expression, 1)->category == Identifier){
                if((aux = search_symbol(symbol_table, getchild(expression, 0)->token)) != NULL || (aux2 = search_symbol(symbol_table, getchild(expression, 1)->token)) != NULL){
                    
                    if(getchild(expression, 0)->category == Identifier && getchild(expression, 1)->category == Identifier){
                        if(strcmp(getchild(expression, 0)->token, getchild(expression, 1)->token) == 0){
                            if(aux || aux2)
                                expression->type = undef_type;
                            return;
                        }
                    }
                    
                    if(aux){
                        aux_p = aux->params_list;
                        getchild(expression, 0)->params_list = aux->params_list;
                    }
                    if(aux2){
                        aux2_p = aux2->params_list;
                        getchild(expression, 1)->params_list = aux2->params_list;
                        //expression->type = undef_type;
                    }

                    aux_p2 = aux_p;
                    aux2_p2 = aux2_p;

                    while(aux_p2 != NULL && aux2_p2 != NULL){
                        if(aux_p2->type != aux2_p2->type)
                            flag_p = 1;
                        
                        aux_p2 = aux_p2->next;
                        aux2_p2 = aux2_p2->next;
                    }

                    if(aux_p2 != NULL){
                        flag_p = 1;
                    }
                    if(aux2_p2 != NULL)
                        flag_p = 1;

                    if(flag_p){
                        if(aux2)
                            expression->type = undef_type;
                        printf("Line %d, column %d: Operator %s cannot be applied to types %s", expression->line, expression->column, symbol_type(expression->category), type_name(getchild(expression, 0)->type));
                        if(aux_p){
                            printf("(");
                            while(aux_p){
                                if(aux_p->next)
                                    printf("%s,", type_name(aux_p->type));
                                else
                                    printf("%s", type_name(aux_p->type));
                                aux_p = aux_p->next;
                            }
                            printf("), %s", type_name(getchild(expression, 1)->type));
                        }else
                            printf(", %s", type_name(getchild(expression, 1)->type));
                        if(aux2_p){
                            printf("(");
                            while(aux2_p){
                                if(aux2_p->next)
                                    printf("%s,", type_name(aux2_p->type));
                                else
                                    printf("%s", type_name(aux2_p->type));
                                aux2_p = aux2_p->next;
                            }
                            printf(")");
                        }
                        printf("\n");   
                    }
                }
            }
}

void check_expression(struct node *expression, struct symbol_list *table){
    //char* category_array[43] = {"Program", "Declaration", "FuncDeclaration", "FuncDefinition", "ParamList", "FuncBody", "ParamDeclaration", "StatList", "If", "While", "Return", "Or", "And", "Eq", "Ne", "Lt", "Gt", "Le", "Ge", "Add", "Sub", "Mul", "Div", "Mod", "Not", "Minus", "Plus", "Store", "Comma", "Call", "BitWiseAnd", "BitWiseXor", "BitWiseOr", "Char", "ChrLit", "Identifier", "Int", "Short", "Natural", "Double", "Decimal", "Void", "Null" };
    //printf("%s\n", category_name[expression->category]);
    
    struct symbol_list* aux = NULL, *aux2 = NULL;
    struct node_list *children = expression->children;

    switch(expression->category){

        case Identifier:
            if(expression->type != undef_type){
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
                int cnt = 0;
                struct node_list *arguments = expression->children->next;
                while(arguments){
                    cnt++;
                    //printf("-->%s %s\n", category_array[arguments->node->category], getchild(expression, 0)->token);
                    check_expression(arguments->node, table);
                    arguments = arguments->next;
                }
                expression->type = expression->children->next->node->type;

                if(cnt-1)       //cnt-1 pq um dos arguments de call é o identifier da function
                    printf("Line %d, column %d: Wrong number of arguments to function %s (got %d, required 0)\n",getchild(expression, 0)->line, getchild(expression, 0)->column, getchild(expression, 0)->token, cnt-1); 
                //has_error = 1;

            }else{
                //printf("ola\n");
                struct node_list *arguments = expression->children->next->next;
                struct param_list *params = search_symbol(symbol_table, getchild(expression, 0)->token)->params_list;
                //printf("-->%s %s\n", category_array[expression->category], getchild(expression, 0)->token);
                
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
            if(getchild(expression, 0)->type == double_type || getchild(expression, 0)->type == undef_type){
                printf("Line %d, column %d: Conflicting types (got %s, expected int)\n", getchild(expression, 0)->line, getchild(expression, 0)->column, type_name(getchild(expression, 0)->type));
            }
            check_expression(getchild(expression, 1), table);
            check_expression(getchild(expression, 2), table);
            break;
        case Comma:
            check_expression(getchild(expression, 0), table);
            check_expression(getchild(expression, 1), table);
            erros_bueda_estranhos2(expression);
            if(!expression->type)
                expression->type = getchild(expression, 1)->type;
            break;
        case Store:
            check_expression(getchild(expression, 0), table);
            check_expression(getchild(expression, 1), table);

            //erros_bueda_estranhos2(expression);

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
            
            erros_bueda_estranhos2(expression);

            if(getchild(expression, 0)->type == undef_type || getchild(expression, 1)->type == undef_type){
                expression->type = undef_type;
                printf("Line %d, column %d: Operator %s cannot be applied to types %s, %s\n", expression->line, expression->column, symbol_type(expression->category), type_name(getchild(expression, 0)->type), type_name(getchild(expression, 1)->type));
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

            if((getchild(expression, 0)->type == undef_type || getchild(expression, 1)->type == undef_type) && (getchild(expression, 0)->type != getchild(expression, 1)->type)){
                printf("Line %d, column %d: Operator %s cannot be applied to types %s, %s\n", expression->line, expression->column, symbol_type(expression->category), type_name(getchild(expression, 0)->type), type_name(getchild(expression, 1)->type));
            }

            break;
        case Plus:
        case Minus:
            check_expression(getchild(expression, 0), table);
            if(getchild(expression, 0)->type == void_type || getchild(expression, 0)->type == undef_type){
                printf("Line %d, column %d: Operator %s cannot be applied to type %s\n", expression->line, expression->column, symbol_type(expression->category), type_name(getchild(expression, 0)->type));
            }
            expression->type = getchild(expression, 0)->type;
            break;
        case Not:
            check_expression(getchild(expression, 0), table);
            expression->type = integer_type;
            
            break;
        case Return:
            check_expression(getchild(expression, 0), table);
            break;
        case While:
            while((children = children->next) != NULL){
                check_expression(children->node, table);
                if(children->node->type == undef_type || children->node->type == double_type || children->node->type == void_type)
                    printf("Line %d, column %d: Conflicting types (got %s, expected int)\n", children->node->line, children->node->column, type_name(children->node->type));
            }
            break;
        default:
            //printf("--> %s\n", category_array[expression->category]);
            break;
    }
}

struct symbol_list * add_to_list_of_tables(struct list_symbol_list * lista, struct node* no){
    //char* category_array[43] = {"Program", "Declaration", "FuncDeclaration", "FuncDefinition", "ParamList", "FuncBody", "ParamDeclaration", "StatList", "If", "While", "Return", "Or", "And", "Eq", "Ne", "Lt", "Gt", "Le", "Ge", "Add", "Sub", "Mul", "Div", "Mod", "Not", "Minus", "Plus", "Store", "Comma", "Call", "BitWiseAnd", "BitWiseXor", "BitWiseOr", "Char", "ChrLit", "Identifier", "Int", "Short", "Natural", "Double", "Decimal", "Void", "Null" };
    struct symbol_list *new_table = (struct symbol_list *) malloc(sizeof(struct symbol_list));
    new_table->next = NULL;
    new_table->type = category_type(getchild(no, 0)->category);
    struct list_symbol_list * aux = lista;
                
    while(aux->next != NULL){
        aux = aux->next;
    }
    aux->list = new_table;
    aux->name = getchild(no, 1)->token;
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
                printf("Line %d, column %d: Symbol %s already defined\n", id->line, id->column, id->token);
                if(flag)
                    add_to_params_list(func, type);
                //has_error = 1;
            }
        }else{
            if(flag)
                add_to_params_list(func, type);
        }
    }

}

void check_funcbody(struct node* funcbody, struct symbol_list *table, enum type tipo){

    struct node_list *children = funcbody->children;
    struct node_list *child;
    int flag = 0;

    while((children = children->next) != NULL){
        switch(children->node->category){
            case Declaration:
                check_declaration(children->node, table);
                break;
            case Return:
                check_expression(getchild(children->node, 0), table);

                if((getchild(children->node, 0)->type != tipo)) {

                    if(getchild(children->node, 0)->type == double_type)
                        flag = 1;
                    if(!getchild(children->node, 0)->type){
                        if(tipo != void_type)
                            flag = 1;
                    }else{
                        if((getchild(children->node, 0)->type == void_type || tipo == void_type) || (getchild(children->node, 0)->type == undef_type || tipo == undef_type))
                            flag = 1;
                    }

                    if(flag){
                        if(getchild(children->node, 0)->type)
                            printf("Line %d, column %d: Conflicting types (got %s, expected %s)\n", getchild(children->node, 0)->line, getchild(children->node, 0)->column, type_name(getchild(children->node, 0)->type), type_name(tipo));
                        else
                            printf("Line %d, column %d: Conflicting types (got void, expected %s)\n", getchild(children->node, 0)->line, getchild(children->node, 0)->column, type_name(tipo));         //Trata do caso return;
                    }
                    
                }
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

    insert_symbol(symbol_table, getchild(function, 1)->token, category_type(getchild(function, 0)->category), function, 0);
    insert_symbol(table, "return", category_type(getchild(function, 0)->category), getchild(function, 1), 0);
    check_ParamList(getchild(function, 2), table, search_symbol(symbol_table, getchild(function, 1)->token));
    check_funcbody(getchild(function, 3), table, category_type(getchild(function, 0)->category));

}

void check_declaration(struct node *declaration, struct symbol_list *table){
    //printf("dec\n");
    //char* category_array[43] = {"Program", "Declaration", "FuncDeclaration", "FuncDefinition", "ParamList", "FuncBody", "ParamDeclaration", "StatList", "If", "While", "Return", "Or", "And", "Eq", "Ne", "Lt", "Gt", "Le", "Ge", "Add", "Sub", "Mul", "Div", "Mod", "Not", "Minus", "Plus", "Store", "Comma", "Call", "BitWiseAnd", "BitWiseXor", "BitWiseOr", "Char", "ChrLit", "Identifier", "Int", "Short", "Natural", "Double", "Decimal", "Void", "Null" };
    
    enum type type = category_type(getchild(declaration, 0)->category);
    struct node *id = getchild(declaration, 1);
    struct node *brothers;
    struct node_list *children;
    int i = 2;

        if(id->category == Identifier){
            while((brothers = getchild(declaration, i)) != NULL){       // Isto faz com que -> int i = i+i o i+i ficam ambos undef
                children = brothers->children;
                while((children = children->next) != NULL){
                    if(children->node->category == Identifier)
                        if(!strcmp(children->node->token, id->token)){
                            children->node->type = undef_type;
                            printf("Line %d, column %d: Unknown symbol %s\n", children->node->line, children->node->column, children->node->token);
                        }
                }
                
                check_expression(brothers, table);
                i++;
            }
            if(search_symbol(table, id->token) == NULL) {
                if(type != void_type){
                    if(getchild(declaration, 2)){
                        if(getchild(declaration, 2)->type == double_type && type != double_type)
                            printf("Line %d, column %d: Conflicting types (got double, expected %s)\n", id->line, id->column, type_name(type));
                        else
                            insert_symbol(table, id->token, type, id, 0); 
                    }else
                        insert_symbol(table, id->token, type, id, 0); 
                }
                else
                    printf("Line %d, column %d: Invalid use of void type in declaration\n", id->line, id->column);
            } else {

                if(type == void_type)
                    printf("Line %d, column %d: Invalid use of void type in declaration\n", id->line, id->column);
                
                if(table != symbol_table)       //Aparentemente so da erro se forem variaveis declaradas dentro da funçao, se forem globais nao ha problema
                    printf("Line %d, column %d: Symbol %s already defined\n", id->line, id->column, id->token);
                else{
                    if(search_symbol(table, id->token)->type != type && search_symbol(table, id->token)->type == double_type)
                        printf("Line %d, column %d: Conflicting types (got %s, expected double)\n", id->line, id->column, type_name(type));
                }
                
                //has_error = 1;
            }
        }

}

void erros_bueda_estranhos(struct node* id, struct node* func){

    enum type type = category_type(getchild(func, 0)->category);
    struct param_list *aux = search_symbol(symbol_table, id->token)->params_list;
    struct node_list *aux2 = getchild(func, 2)->children->next;
    int flag = 0;

        while(aux && aux2){
            if(aux->type != category_type(getchild(aux2->node, 0)->category)){
                flag = 1;
            }
            aux = aux->next;
            aux2 = aux2->next;
        }

        aux2 = getchild(func, 2)->children->next;
        aux = search_symbol(symbol_table, id->token)->params_list;

        if(type != (search_symbol(symbol_table, id->token)->type) || flag){
            printf("Line %d, column %d: Conflicting types (got %s", id->line, id->column, type_name(type));
            if(aux2){
                printf("(");
                while(aux2){
                    if(aux2->next)
                        printf("%s,", type_name(category_type(getchild(aux2->node, 0)->category)));
                    else
                        printf("%s", type_name(category_type(getchild(aux2->node, 0)->category)));
                    aux2 = aux2->next;
                }
                printf(")");
            }
            printf(", expected %s", type_name(search_symbol(symbol_table, id->token)->type));
            if(aux){
                printf("(");
                while(aux){
                    if(aux->next)
                        printf("%s,", type_name(aux->type));
                    else
                        printf("%s", type_name(aux->type));
                    aux = aux->next;
                }
                printf(")");
            }
            printf(")\n");
        }
}

int check_funcdeclatarion(struct node *func_dec, struct list_symbol_list * lista){
    //printf("func_dec\n");
    //char* category_array[43] = {"Program", "Declaration", "FuncDeclaration", "FuncDefinition", "ParamList", "FuncBody", "ParamDeclaration", "StatList", "If", "While", "Return", "Or", "And", "Eq", "Ne", "Lt", "Gt", "Le", "Ge", "Add", "Sub", "Mul", "Div", "Mod", "Not", "Minus", "Plus", "Store", "Comma", "Call", "BitWiseAnd", "BitWiseXor", "BitWiseOr", "Char", "ChrLit", "Identifier", "Int", "Short", "Natural", "Double", "Decimal", "Void", "Null" };
    enum type type = category_type(getchild(func_dec, 0)->category);
    struct node *id = getchild(func_dec, 1);
    struct node_list *ParamList = getchild(func_dec, 2)->children;
    int cnt = 0;
    
    while((ParamList = ParamList->next) != NULL){
        if(getchild(ParamList->node, 0)->category == Void && getchild(ParamList->node, 1)){
            printf("Line %d, column %d: Invalid use of void type in declaration\n", getchild(ParamList->node, 0)->line, getchild(ParamList->node, 0)->column);
            return 0;
        }
        else{
            if((getchild(ParamList->node, 0)->category == Void && ParamList->next) || (cnt && getchild(ParamList->node, 0)->category == Void)){      //Sempre que ha void deve dar erro a nao ser q seja um unico parametro void 
                printf("Line %d, column %d: Invalid use of void type in declaration\n", getchild(ParamList->node, 0)->line, getchild(ParamList->node, 0)->column);  //int main(void) deve ser aceite, e int main(void, int) nao, e int main(int, void) tambem nao
                return 0;
            }
        }
        cnt++;
    }

    if(search_symbol(symbol_table, id->token) == NULL) {

        insert_symbol(symbol_table, id->token, type, id, 0);
        check_ParamList(getchild(func_dec, 2), NULL, search_symbol(symbol_table, id->token));

        struct symbol_list *aux = (struct symbol_list *) malloc(sizeof(struct symbol_list));
        aux->next = NULL;
        struct node_list *children = getchild(func_dec, 2)->children;

        while((children = children->next) != NULL){
            if(getchild(children->node, 1))
                insert_symbol(aux, getchild(children->node, 1)->token, category_type(getchild(children->node, 0)->category), getchild(children->node, 1), 0);
        }

        return 1;

    }else{
        erros_bueda_estranhos(id, func_dec);
        
        if(search_symbol(symbol_table, id->token)->type == type)
            print_erros(func_dec);
        
    } 

    return 0;
}

void print_erros(struct node* node){
    struct node_list* children = getchild(node, 2)->children->next;
    struct param_list* aux = search_symbol(symbol_table, getchild(node, 1)->token)->params_list;

    while(children && aux){
        aux = aux->next;
        children = children->next;
    }

    if(children || aux ){
        printf("Line %d, column %d: Conflicting types (got %s", getchild(node,1)->line, getchild(node,1)->column ,type_name(category_type(getchild(node, 0)->category)));
        if((children = getchild(node, 2)->children->next) != NULL){
            printf("(");
            while(children){
                if(children->next)
                    printf("%s,", type_name(category_type(getchild(children->node, 0)->category)));
                else
                    printf("%s", type_name(category_type(getchild(children->node, 0)->category)));
                children = children->next;
            }
            printf("), expected %s", type_name(search_symbol(symbol_table, getchild(node, 1)->token)->type));
        }else
            printf(", expected %s", type_name(search_symbol(symbol_table, getchild(node, 1)->token)->type));

        if((aux = search_symbol(symbol_table, getchild(node, 1)->token)->params_list) != NULL){
            printf("(");
            while(aux){
                if(aux->next)
                    printf("%s,", type_name(aux->type));
                else
                    printf("%s", type_name(aux->type));
                aux = aux->next;
            }
            printf(")");
        }
        printf(")");
        printf("\n");
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
    int flag, flag_params = 0;
    while((child = child->next) != NULL){

        switch(child->node->category){
            
            case Declaration:
                //printf("%d-->%s\n", ++num, getchild(child->node, 1)->token);
                check_declaration(child->node, symbol_table);
                break;

            case FuncDefinition:

                if(search_table(lista, getchild(child->node, 1)->token) == NULL){
                    if(getchild(getchild(child->node, 3), 0) == NULL){  //Funcbody != NULL e return != Void
                        new_table = add_to_list_of_tables(lista, child->node); 
                        check_function(child->node, new_table);                  
                    }else{
                        if(getchild(getchild(child->node, 3), 0) != NULL){
                            new_table = add_to_list_of_tables(lista, child->node);
                            check_function(child->node, new_table);
                        }
                    }
                    
                }else{
                    if(search_table(lista, getchild(child->node, 1)->token)->next){      // Se o return ainda nao existir a funçao ainda nao existe
                        //show_symbol_table(search_table(lista, getchild(child->node, 1)->token));
                        printf("Line %d, column %d: Symbol %s already defined\n", getchild(child->node, 1)->line, getchild(child->node, 1)->column, getchild(child->node, 1)->token);

                    }else{
                        print_erros(child->node);
                        erros_bueda_estranhos(getchild(child->node, 1), child->node);       
                        
                        // Check type and params equal 
                        if(search_table(lista, getchild(child->node, 1)->token)->type == category_type(getchild(child->node, 0)->category)){
                            
                            struct param_list* aux = search_symbol(symbol_table, getchild(child->node, 1)->token)->params_list;
                            struct node_list* paramList = getchild(child->node, 2)->children->next; 
                            //printf("%s\n",getchild(child->node, 1)->token);
                            while(aux && paramList){
                                //printf("%s %s\n", type_name(aux->type), type_name(category_type(getchild(paramList->node, 0)->category)));
                                if(aux->type != category_type(getchild(paramList->node, 0)->category)){
                                    flag_params = 1;
                                }
                                aux = aux->next;
                                paramList = paramList->next;
                            }

                            if(aux)
                                flag_params = 1;
                            if(paramList)
                                flag_params = 1;
                            if(!flag_params)
                                check_function(child->node, search_table(lista, getchild(child->node, 1)->token));
                        }    
                    }
                }
                
                break;

            case FuncDeclaration:
                //printf("%s\n", category_array[child->node->category]);
                flag = check_funcdeclatarion(child->node, lista);
                if(flag){
                    new_table = add_to_list_of_tables(lista, child->node);
                }

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
        if(aux->list->next){
            printf("===== Function %s Symbol Table =====\n", aux->name);
            show_symbol_table(aux->list);
            printf("\n");
        }
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
            if(node->line != 0)
                printf("Line %d, column %d: Symbol %s already defined\n", node->line, node->column, node->token);
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
    if(identifier == NULL)
        return NULL;
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
