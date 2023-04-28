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
    if (index >= pow(2, depth - 1) - 1 || index <= pow(2, depth) - 2)
    {
        tree[index].dirty = false;
        return;
    }

    // children of ith node are at 2i+1 and 2i+2
    int l = 2 * index + 1;
    int r = 2 * index + 2;

    /* if the index is not a leaf node, moundify its children
     the Mnode with the least value is swapped with the parent node
     and moundify is called on the swapped node */

    // child l <= child r
    if ((tree[l].list->value <= tree[r].list->value) && (tree[l].list->value < tree[index].list->value))
    {
        swap(tree, l, r);
        moundify(tree, l, depth);
    }
    // child l > child r
    else if ((tree[l].list->value > tree[r].list->value) && (tree[r].list->value < tree[index].list->value))
    {
        swap(tree, l, r);
        moundify(tree, r, depth);
    }
    // properly moundified
    else
    {
        tree[index].dirty = false;
        return;
    }
}

int extractMin(Mnode tree[], int depth)
{
    if (tree[0].list->value == INT_MAX)
    {
        return INT_MAX;
    }
    // minimum value is stored in the root node's list first element
    int result = tree[0].list->value;
    Lnode *temp = tree[0].list;
    tree[0].list = tree[0].list->next;
    free(temp);

    // moundify the tree, starting from the root node
    moundify(tree, 0, depth);

    return result;
}

// function for swapping any two nodes
void swap(Mnode tree[], int l, int r)
{
    Mnode temp = tree[l];
    tree[l] = tree[r];
    tree[r] = temp;
}