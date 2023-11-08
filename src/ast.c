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

void addbrother(struct node *brother, struct node *new_brother){
    if (brother == NULL) {
        
    }else{
        struct node_list *new = malloc(sizeof(struct node_list));
        new->node = new_brother;
        new->next = NULL;

        if (brother->brotherhood == NULL) {
            brother->brotherhood = new;
        } else {
            struct node_list *temp = brother->brotherhood;
            while(temp->next != NULL)
                temp = temp->next;
            temp->next = new;
        }
    }
}



void show(struct node *node, int depth) {

    char* category_array[43] = {"Program", "Declaration", "FuncDeclaration", "FuncDefinition", "ParamList", "FuncBody", "ParamDeclaration", "StatList", "If", "While", "Return", "Or", "And", "Eq", "Ne", "Lt", "Gt", "Le", "Ge", "Add", "Sub", "Mul", "Div", "Mod", "Not", "Minus", "Plus", "Store", "Comma", "Call", "BitWiseAnd", "BitWiseXor", "BitWiseOr", "Char", "ChrLit", "Identifier", "Int", "Short", "Natural", "Double", "Decimal", "Void", "Null" };
    
    if(node){
        for(int i=0 ; i <depth; i++){
            printf("..");
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

        struct node_list *brother = node->brotherhood;
        while(brother){
            show(brother->node, depth);
            brother = brother->next;
        }
    }

}


