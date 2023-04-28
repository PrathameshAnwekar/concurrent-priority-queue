#include <stdlib.h>
#include "lnode.h"

Lnode* createNode(int value){
    Lnode* newnode = (Lnode*)malloc(sizeof(Lnode));
    newnode->value=value;
    newnode->next=NULL;
    return newnode;
}