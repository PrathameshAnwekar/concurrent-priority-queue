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

void insertAtBeginning(Mnode tree[],int index, int value);
void printList(Mnode head);
void insert(int value, int *depth, Mnode tree[]);
int randLeaf(int depth);
int val(Mnode head);
int findInsertionPoint(int value, int *depth, Mnode tree[]);
int extractMin(Mnode tree[], int);
void moundify(Mnode tree[], int index, int depth);
void swap(Mnode tree[], int l, int r);
#endif