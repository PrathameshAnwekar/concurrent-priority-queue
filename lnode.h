#ifndef LNODE_H
#define LNODE_H

struct Lnode
{
    int val;
    Lnode* list;
};
typedef struct Lnode Lnode;
#endif