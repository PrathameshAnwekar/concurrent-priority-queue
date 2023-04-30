#ifndef LNODE_H
#define LNODE_H

typedef struct Lnode Lnode; 
typedef struct Lnode
{
    int value;
    Lnode *next;
} Lnode;

Lnode *createNode(int value);

#endif
