#ifndef MNODE_H
#define MNODE_H

#include <stdbool.h>
#include "lnode.h"

struct Mnode
{
    bool dirty;
    int counter;
    Lnode* list;
};
typedef struct Mnode Mnode;
#endif