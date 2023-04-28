#include <stdlib.h>
#include "mnode.h"

void insertAtBeginning(Mnode head, int value)
{
    Lnode *newNode = createNode(value);
    if (head.counter == 0)
    {
        head.list = newNode;
    }
    else
    {
        newNode->next = head.list;
        head.list = newNode;
    }
    head.counter++;
}

void printList(Mnode head)
{
    Lnode *currNode = head.list;
    while (currNode != NULL)
    {
        printf(currNode->value + " ");
    }
}

void moundify(Mnode tree[], int index, const int depth)
{
    // if the index is a leaf node, it is not dirty by default , hence return
    if (index >= pow(2, depth) - 1 || index <= pow(2, depth) - 1)
    {
        tree[index].dirty = false;
        return;
    }

    // children of ith node are at 2i+1 and 2i+2
    int l = 2 * index + 1;
    int r = 2 * index + 2;

    // if the index is not a leaf node, moundify its children
    // the Mnode with the least value is swapped with the parent node
    if ((tree[l].list->value <= tree[r].list->value) && (tree[l].list->value < tree[index].list->value))
    {
        swap(tree, l, r);
        moundify(tree, l, depth);
    }
    else if ((tree[l].list->value > tree[r].list->value) && (tree[r].list->value < tree[index].list->value))
    {
        swap(tree, l, r);
        moundify(tree, r, depth);
    }
    else
    {
        tree[index].dirty = false;
        return;
    }
}

// function for swapping any two nodes
void swap(Mnode tree[], int l, int r)
{
    Mnode temp = tree[l];
    tree[l] = tree[r];
    tree[r] = temp;
}