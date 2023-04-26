#ifndef LNODE_H
#define LNODE_H

typedef struct 
{
    int value;
    Lnode* next;
} Lnode;

Lnode* createNode(int val);
Lnode* insertAtBeginning(Lnode* head, int val);
void printList(Lnode* head);
#endif

