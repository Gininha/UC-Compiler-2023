#ifndef _SEMANTICS_H
#define _SEMANTICS_H

#include "ast.h"

struct symbol_list {
    char *identifier;
    enum type type;
    bool param;
    struct param_list *params_list;
    struct node *node;
    struct symbol_list *next;
};

struct list_symbol_list {
    char *name;
    struct symbol_list *list;
    struct list_symbol_list *next;
};

void check_program(struct node *program);
void check_declaration(struct node *declaration, struct symbol_list *table);
void check_expression(struct node *expression, struct symbol_list *table);
void print_erros(struct node* node);

struct symbol_list *insert_symbol(struct symbol_list *symbol_table, char *identifier, enum type type, struct node *node, int is_param);
struct symbol_list *search_symbol(struct symbol_list *symbol_table, char *identifier);
void show_symbol_table(struct symbol_list *table);

#endif
