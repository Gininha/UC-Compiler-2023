#ifndef _AST_H
#define _AST_H

enum category { Program, Declaration, FuncDeclaration, FuncDefinition, ParamList, FuncBody, ParamDeclaration, StatList, If, While, Return, Or, And, Eq, Ne, Lt, Gt, Le, Ge, Add, Sub, Mul, Div, Mod, Not, Minus, Plus, Store, Comma, Call, BitWiseAnd, BitWiseXor, BitWiseOr, Char, ChrLit, Identifier, Int, Short, Natural, Double, Decimal, Void, Null };

struct node {
    enum category category;
    char *token;
    struct node_list *children;
    struct node *parent;
    struct node_list *brotherhood;
};

struct node_list {
    struct node *node;
    struct node_list *next;
};

struct node *newnode(enum category category, char *token);
void set_father(struct node* father, struct node* child);
void print_d3(struct node *node);
void addchild(struct node *parent, struct node *child);
void addbrother(struct node *brother, struct node *new_brother);
void show(struct node *node, int depth);
void Remove_tree(struct node *node);

#endif
