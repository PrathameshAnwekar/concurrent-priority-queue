#ifndef MNODE_H
#define MNODE_H

#include <stdbool.h>
#include "lnode.h"

typedef struct 
{
    bool dirty;
    int counter;
    Lnode* list;
}Mnode;

#endif