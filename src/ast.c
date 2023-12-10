#include "ast.h"
#include <stdio.h>
#include <stdlib.h>

// create a node of a given category with a given lexical symbol
struct node *newnode(enum category category, char *token) {
    // char* category_array[43] = {"Program", "Declaration", "FuncDeclaration", "FuncDefinition", "ParamList", "FuncBody", "ParamDeclaration", "StatList", "If", "While", "Return", "Or", "And", "Eq", "Ne", "Lt", "Gt", "Le", "Ge", "Add", "Sub", "Mul", "Div", "Mod", "Not", "Minus", "Plus", "Store", "Comma", "Call", "BitWiseAnd", "BitWiseXor", "BitWiseOr", "Char", "ChrLit", "Identifier", "Int", "Short", "Natural", "Double", "Decimal", "Void", "Null" };
    // printf("Created node %s\n", category_array[category]);
    struct node *new = malloc(sizeof(struct node));
    new->category = category;
    new->token = token;
    new->children = malloc(sizeof(struct node_list));
    new->children->node = NULL;
    new->children->next = NULL;
    return new;
}

// append a node to the list of children of the parent node
void addchild(struct node *parent, struct node *child) {
    // char* category_array[43] = {"Program", "Declaration", "FuncDeclaration", "FuncDefinition", "ParamList", "FuncBody", "ParamDeclaration", "StatList", "If", "While", "Return", "Or", "And", "Eq", "Ne", "Lt", "Gt", "Le", "Ge", "Add", "Sub", "Mul", "Div", "Mod", "Not", "Minus", "Plus", "Store", "Comma", "Call", "BitWiseAnd", "BitWiseXor", "BitWiseOr", "Char", "ChrLit", "Identifier", "Int", "Short", "Natural", "Double", "Decimal", "Void", "Null" };
    // printf("adding child %s ", category_array[child->category]);
    // printf("my father is %s\n", category_array[parent->category]);
    if (child && parent) {
        child->parent = parent;
        struct node_list *new = malloc(sizeof(struct node_list));
        new->node = child;
        new->next = NULL;
        struct node_list *children = parent->children;
        while (children->next != NULL)
            children = children->next;
        children->next = new;

        struct node_list *brothers = child->brotherhood;
        while (brothers != NULL) {
            addchild(parent, brothers->node);
            brothers = brothers->next;
        }

        struct node_list *brothers2 = child->brotherhood;
        while (brothers2 != NULL) {
            struct node_list *aux = brothers2;
            brothers2 = brothers2->next;
            free(aux);
        }

        child->brotherhood = NULL;
    }
}

void print_d3(struct node *node) {
    char *category_array[43] = {"Program", "Declaration", "FuncDeclaration", "FuncDefinition", "ParamList", "FuncBody", "ParamDeclaration", "StatList", "If", "While", "Return", "Or", "And", "Eq", "Ne", "Lt", "Gt", "Le", "Ge", "Add", "Sub", "Mul", "Div", "Mod", "Not", "Minus", "Plus", "Store", "Comma", "Call", "BitWiseAnd", "BitWiseXor", "BitWiseOr", "Char", "ChrLit", "Identifier", "Int", "Short", "Natural", "Double", "Decimal", "Void", "Null"};
    if (node) {
        printf("%s", category_array[node->category]);
        if (node->token)
            printf("(%s)", node->token);
        printf("\n");

        struct node_list *aux = node->children->next;
        while (aux) {
            print_d3(aux->node);
            aux = aux->next;
        }

        aux = node->brotherhood;
        while (aux) {
            print_d3(aux->node);
            aux = aux->next;
        }
    }
}

void addbrother(struct node *brother, struct node *new_brother) {

    if (brother && new_brother) {
        // char* category_array[43] = {"Program", "Declaration", "FuncDeclaration", "FuncDefinition", "ParamList", "FuncBody", "ParamDeclaration", "StatList", "If", "While", "Return", "Or", "And", "Eq", "Ne", "Lt", "Gt", "Le", "Ge", "Add", "Sub", "Mul", "Div", "Mod", "Not", "Minus", "Plus", "Store", "Comma", "Call", "BitWiseAnd", "BitWiseXor", "BitWiseOr", "Char", "ChrLit", "Identifier", "Int", "Short", "Natural", "Double", "Decimal", "Void", "Null" };
        if (brother->parent != NULL) {

            // printf("adding new brother %s old brother is %s\n", category_array[new_brother->category], category_array[brother->category]);

            addchild(brother->parent, new_brother);
        } else {

            // printf("Brother %s in %s queue\n", category_array[new_brother->category], category_array[brother->category]);

            struct node_list *brothers = brother->brotherhood;

            if (brothers) {
                while (brothers->next != NULL) {
                    brothers = brothers->next;
                }

                brothers->next = malloc(sizeof(struct node_list));
                brothers->next->node = new_brother;
                brothers->next->next = NULL;
            } else {
                brother->brotherhood = malloc(sizeof(struct node_list));
                brother->brotherhood->node = new_brother;
                brother->brotherhood->next = NULL;
            }
        }
    }
}

struct node *getchild(struct node *parent, int position) {
    struct node_list *children = parent->children;
    while ((children = children->next) != NULL)
        if (position-- == 0)
            return children->node;
    return NULL;
}

void show(struct node *node, int depth) {

    char *category_array[43] = {"Program", "Declaration", "FuncDeclaration", "FuncDefinition", "ParamList", "FuncBody", "ParamDeclaration", "StatList", "If", "While", "Return", "Or", "And", "Eq", "Ne", "Lt", "Gt", "Le", "Ge", "Add", "Sub", "Mul", "Div", "Mod", "Not", "Minus", "Plus", "Store", "Comma", "Call", "BitWiseAnd", "BitWiseXor", "BitWiseOr", "Char", "ChrLit", "Identifier", "Int", "Short", "Natural", "Double", "Decimal", "Void", "Null"};
    // char* type_array[4] = {"int", "double", "char", "no_type"};

    if (node) {
        for (int i = 0; i < depth; i++) {
            printf("..");
        }

        printf("%s", category_array[node->category]);
        if (node->token)
            printf("(%s)", node->token);
        if (node->type)
            printf(" - %s", type_name(node->type));
        if (node->params_list) {
            printf("(");
            struct param_list *aux = node->params_list;
            while (aux) {
                if (aux->next)
                    printf("%s,", type_name(aux->type));
                else
                    printf("%s", type_name(aux->type));
                aux = aux->next;
            }
            printf(")");
        }
        printf("\n");

        struct node_list *aux = node->children->next;
        while (aux) {
            show(aux->node, depth + 1);
            aux = aux->next;
        }
    }
}

void Remove_conns(struct node_list *children) {

    struct node_list *child = children;
    // free(node->children);
    while (child != NULL) {
        struct node_list *temp = child;
        child = child->next;
        free(temp);
    }
}

void Tracker(struct node *node, int line, int column) {
    node->line = line;
    node->column = column;
}

void Remove_tree(struct node *node) {

    if (node) {

        struct node_list *child = node->children->next;
        free(node->children);
        while (child != NULL) {
            Remove_tree(child->node);
            struct node_list *tmp = child;
            child = child->next;
            free(tmp);
        }

        if (node->token)
            free(node->token);

        while (node->brotherhood != NULL) {
            struct node_list *aux = node->brotherhood;
            node->brotherhood = node->brotherhood->next;
            free(aux);
        }

        free(node);
    }
}
