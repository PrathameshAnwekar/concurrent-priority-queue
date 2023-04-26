#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdbool.h>
#include "lnode.h"
#include "mnode.h"

Lnode* createNode(int value);

void insertAtBeginning(Mnode head, int value);

void printList(Mnode head);

#endif
