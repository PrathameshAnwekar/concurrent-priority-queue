#ifndef MNODE_H
#define MNODE_H

#include <stdbool.h>
#include "lnode.h"

typedef struct
{
    bool dirty;
    int counter;
    Lnode *list;
} Mnode;

void insertAtBeginning(Mnode head, int value);

void printList(Mnode head);

void insert(Mnode tree[], int value);
int extractMin(Mnode tree[]);
void moundify(Mnode tree[], int index, int depth);
void swap(Mnode tree[], int l, int r);
#endif