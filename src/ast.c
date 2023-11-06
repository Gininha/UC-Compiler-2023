#include <stdlib.h>
#include <stdio.h>
#include "ast.h"

// create a node of a given category with a given lexical symbol
struct node *newnode(enum category category, char *token) {
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
    struct node_list *new = malloc(sizeof(struct node_list));
    new->node = child;
    new->next = NULL;
    struct node_list *children = parent->children;
    while(children->next != NULL)
        children = children->next;
    children->next = new;
}

void show(struct node *node, int depth) {

    char* category_array[42] = {"Program", "Declaration", "FuncDeclaration", "FuncDefinition", "ParamList", "FuncBody", "ParamDeclaration", "StatList", "If", "While", "Return", "Or", "And", "Eq", "Ne", "Lt", "Gt", "Le", "Ge", "Add", "Sub", "Mul", "Div", "Mod", "Not", "Minus", "Plus", "Store", "Comma", "Call", "BitWiseAnd", "BitWiseXor", "BitWiseOr", "Char", "ChrLit", "Identifier", "Int", "Short", "Natural", "Double", "Decimal", "Void" };
    
    for(int i=0 ; i <depth; i++){
        printf("__");
    }
    printf("%s", category_array[node->category]);
    if(node->token)
        printf("(%s)", node->token);
    printf("\n");
    struct node_list *aux = node->children->next;
    while(aux){
        show(aux->node, depth+1);
        aux = aux->next;
    }
}

