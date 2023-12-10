#ifndef _AST_H
#define _AST_H

#include <stdbool.h>

enum category {Program, Declaration, FuncDeclaration, FuncDefinition, ParamList, FuncBody, ParamDeclaration, StatList, If, While, Return, Or, And, Eq, Ne, Lt, Gt, Le, Ge, Add, Sub, Mul, Div, Mod, Not, Minus, Plus, Store, Comma, Call, BitWiseAnd, BitWiseXor, BitWiseOr, Char, ChrLit, Identifier, Int, Short, Natural, Double, Decimal, Void, Null};
enum type {kek, void_type, undef_type, char_type, short_type, integer_type, double_type, no_type};

#define type_name(type) (type == integer_type ? "int" : (type == double_type ? "double" : (type == char_type ? "char" : (type == short_type ? "short" : (type == void_type ? "void" : (type == undef_type ? "undef" : "none"))))))
#define category_type(category) (category == Int ? integer_type : (category == Double ? double_type : (category == Char ? char_type : (category == Short ? short_type : (category == Void ? void_type: no_type)))))
#define symbol_type(category) (category == Or ? "||" : (category == And ? "&&" : (category == Mod ? "%" : (category == BitWiseAnd ? "&" : (category == BitWiseOr ? "|" : (category == BitWiseXor ? "^" : (category == Eq ? "==" : (category == Ne ? "!=" : (category == Le ? "<=" : (category == Ge ? ">=" : (category == Lt ? "<" : (category == Gt ? ">" : (category == Plus ? "+" : (category == Add ? "+" : (category == Mul ? "*" : (category == Div ?  "/" : (category == Comma ? "," : "-")))))))))))))))))

struct node {
    enum category category;
    enum type type;
    struct param_list *params_list;
    char *token;
    struct node_list *children;
    struct node *parent;
    struct node_list *brotherhood;
    int line, column;
};

struct param_list {
    enum type type;
    struct param_list *next;
};

struct node_list {
    struct node *node;
    struct node_list *next;
};

struct node *newnode(enum category category, char *token);
void set_father(struct node *father, struct node *child);
void print_d3(struct node *node);
void addchild(struct node *parent, struct node *child);
void addbrother(struct node *brother, struct node *new_brother);
struct node *getchild(struct node *parent, int position);
void show(struct node *node, int depth);
void Remove_tree(struct node *node);
void Remove_conns(struct node_list *children);
void Tracker(struct node *node, int line, int column);

#endif
