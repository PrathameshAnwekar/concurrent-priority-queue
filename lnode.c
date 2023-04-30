#include <stdlib.h>
#include <stdio.h>
#include "lnode.h"

Lnode *createNode(int value)
{
    Lnode *newnode = (Lnode *)malloc(sizeof(Lnode));
    newnode->value = value;
    newnode->next = NULL;
    printf("created node with value %d\n", value);
    return newnode;
}