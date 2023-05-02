#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>

typedef struct Lnode Lnode;
typedef struct Lnode
{
    int value;
    Lnode *next;
} Lnode;

typedef struct Mnode
{
    bool dirty;
    int counter;
    Lnode *list;
} Mnode;

int readData(int numbers[]);
Lnode *createNode(int value);
void insert(int value, int *depth, Mnode *tree);
int findInsertionPoint(int value, int *depth, Mnode *tree);
void insertAtBeginning(Mnode *tree, int index, int value);
int randLeaf(int depth);
int val(Mnode head);
int binarySearch(Mnode *tree, int leaf, int depth, int value);
int extractMin(Mnode *tree, int depth);
void moundify(Mnode *tree, int index, int depth);
void swap(Mnode *tree, int l, int r);
Mnode *realloc_Mnode(int depth, Mnode *tree);

int MAX_NUMBERS = 105009;

int main()
{
    int depth = 1;
    int numbers[MAX_NUMBERS];
    int count = readData(numbers);
    Mnode *oldTree = (Mnode *)malloc(sizeof(Mnode));
    Mnode *tree = realloc_Mnode(depth, oldTree);
    printf("The value of tree[0] is currently %d\n", tree[0].list->value);
    for (int i = 0; i < 10; i++)
    {
        insert(numbers[i], &depth, tree);
        printf("\n\n\n\n\n\n");
    }

    for(int i = 0; i < 10; i++)printf("this is the min %d\n", extractMin(tree, depth));
    return 0;
}

int readData(int numbers[])
{
    FILE *fp;
    int count = 0;
    int number;
    fp = fopen("data.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }
    while (fscanf(fp, "%d", &number) != EOF)
    {
        if (count >= MAX_NUMBERS)
        {
            printf("Too many numbers in file\n");
            return 1;
        }
        numbers[count] = number;
        count++;
    }
    fclose(fp);
    return count;
}

Lnode *createNode(int value)
{
    Lnode *newnode = (Lnode *)malloc(sizeof(Lnode));
    newnode->value = value;
    newnode->next = NULL;
    return newnode;
}

void insert(int value, int *depth, Mnode *tree)
{
    int index = findInsertionPoint(value, depth, tree);
    insertAtBeginning(tree, index, value);
}

int findInsertionPoint(int value, int *depth, Mnode *tree)
{
    int threshold = 3;
    for (int i = 1; i <= threshold; i++)
    {
        int leaf = randLeaf(*depth);
        if (val(tree[leaf]) >= value)
        {
            return binarySearch(tree, leaf, *depth, value);
        }
    }
    *depth = (*depth) + 1;
    tree = realloc_Mnode(*depth, tree);
    return binarySearch(tree, randLeaf(*depth), *depth, value);
}

void insertAtBeginning(Mnode *tree, int index, int value)
{
    Lnode *newNode = createNode(value);
    newNode->next = tree[index].list;
    tree[index].list = newNode;
    tree[index].counter++;
}

int randLeaf(int depth)
{
    if (depth == 1)
        return 0;
    int lower = (int)pow(2, depth - 1) - 1, upper = (int)pow(2, depth) - 2;
    int random = (rand() % (upper - lower + 1)) + lower;
    return random;
}

int val(Mnode head)
{
    if (head.list == NULL)
        return INT_MAX;
    else
        return head.list->value;
}

int binarySearch(Mnode *tree, int leaf, int depth, int value)
{
    int lo = 0, hi = depth-1, mid, ans = leaf;
    int indexes[depth];
    for (int j = depth; j >= 1; j--)
    {
        indexes[j - 1] = leaf;
        leaf = (leaf - 1) / 2;
    }
    while (lo <= hi)
    {
        mid = lo + (hi - lo) / 2;
        if (val(tree[indexes[mid]]) >= value)
        {
            ans = indexes[mid];
            hi = mid - 1;
        }
        else
        {
            lo = mid + 1;
        }
    }
    return ans;
}

void moundify(Mnode *tree, int index, int depth)
{
    // if the index is a leaf node, it is not dirty by default , hence return
    if (index >= ((int)pow(2, depth - 1) - 1) && index <= ((int)pow(2, depth) - 2))
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
        swap(tree, l, index);
        moundify(tree, l, depth);
    }
    // child l > child r
    else if ((tree[l].list->value > tree[r].list->value) && (tree[r].list->value < tree[index].list->value))
    {
        swap(tree, index, r);
        moundify(tree, r, depth);
    }
    // properly moundified
    else
    {
        tree[index].dirty = false;
    }
}

int extractMin(Mnode *tree, int depth)
{
    if (tree[0].list == NULL)
    {
        return INT_MAX;
    }
    // minimum value is stored in the root node's list first element
    int result = tree[0].list->value;
    Lnode *temp = tree[0].list;
    tree[0].list = temp->next;
    temp->next=NULL;
    tree[0].dirty = true;
    free(temp);

    // moundify the tree, starting from the root node
    moundify(tree, 0, depth);
    return result;
}

// function for swapping any two nodes
void swap(Mnode *tree, int l, int r)
{
    Mnode temp = tree[l];
    tree[l] = tree[r];
    tree[r] = temp;
}

Mnode *realloc_Mnode(int depth, Mnode *tree)
{
    tree= (Mnode*)malloc(1000000*sizeof(Mnode));
    for(int i=0;i<1000000;i++)
    {
        tree[i].dirty = false;
        tree[i].counter = 0;
        tree[i].list = createNode(INT_MAX);    
    }
    return tree;
}

// Mnode *realloc_Mnode(int depth, Mnode *tree)
// {
//     Mnode* newtree = (Mnode *)malloc(((int)pow(2, depth) - 1) * sizeof(Mnode));
//     for (int i = 0; i < (int)pow(2, depth - 1) - 1; i++)
//     {
//         newtree[i].list = tree[i].list;
//         newtree[i].dirty = tree[i].dirty;
//         newtree[i].counter = tree[i].counter;
//     }
//     for (int i = (int)pow(2, depth - 1) - 1; i < (int)pow(2, depth) - 1; i++)
//     {
//         newtree[i].dirty = false;
//         newtree[i].counter = 0;
//         newtree[i].list = createNode(INT_MAX);
//     }
//     // free(tree);
//     return newtree;
// }
