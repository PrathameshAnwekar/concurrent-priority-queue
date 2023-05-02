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
Mnode *malloc_Mnode(int depth, Mnode *tree);

int main()
{
    int count = 0;
    int depth = 1;

    // initializing the tree / priority queue with depth 1.
    Mnode *tree = malloc_Mnode(depth, tree);

    FILE *fp;
    int number;

    // opening the file
    fp = fopen("data.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }

    // inseting all the numbers in the file into the tree.
    while (fscanf(fp, "%d", &number) != EOF)
    {
        insert(number, &depth, tree);
        count++;
    }
    fclose(fp);
    printf("The initial depth of the tree is: %d\n", depth);
    // extracting all the numbers from the tree to verify the correctness of the program.
    for (int i = 0; i < count; i++)
    printf("This is the extracted minimum number: %d \n ", extractMin(tree, depth));
    return 0;
}

// creates a new Lnode with the given value and returns it.
Lnode *createNode(int value)
{
    Lnode *newnode = (Lnode *)malloc(sizeof(Lnode));
    newnode->value = value;
    newnode->next = NULL;
    return newnode;
}

/*  inserts a new value into the tree.
    The function first finds the insertion point
    and then inserts the value at the beginning
    of the list of the corresponding Mnode.
*/
void insert(int value, int *depth, Mnode *tree)
{
    int index = findInsertionPoint(value, depth, tree);
    insertAtBeginning(tree, index, value);
}

int min(int a, int b){
    return a < b ? a : b;
}

/*  firstly it finds a suitable leaf node for insertion.
    Once found, it calls binary search on the path from
    the root to the leaf node to find the insertion point.
    If too many unsuitable leaves are selected
    (indicated by a tunable THRESHOLD parameter), the
    mound is expanded by one level.
    Then binary search is called on a random leaf node
    present in the new depth.
    Threshold is set dynamically, since we have observed that 
    the depth converges to its minimum value after
    threshold is increased beyond a certain point.
*/
int findInsertionPoint(int value, int *depth, Mnode *tree)
{
    int threshold = min((int)pow(2, *depth ), 100);
    for (int i = 1; i <= threshold; i++)
    {
        int leaf = randLeaf(*depth);
        if (val(tree[leaf]) >= value)
        {
            return binarySearch(tree, leaf, *depth, value);
        }
    }
    *depth = (*depth) + 1;
    return binarySearch(tree, randLeaf(*depth), *depth, value);
}

/*  inserts a new node at the beginning of the list
    of the corresponding Mnode.
*/
void insertAtBeginning(Mnode *tree, int index, int value)
{
    Lnode *newNode = createNode(value);
    newNode->next = tree[index].list;
    tree[index].list = newNode;
    tree[index].counter++;
}

// returns a index of a random leaf node at the given depth.
int randLeaf(int depth)
{
    if (depth == 1)
        return 0;
    int lower = (int)pow(2, depth - 1) - 1, upper = (int)pow(2, depth) - 2;
    int random = (rand() % (upper - lower + 1)) + lower;
    return random;
}

// returns the first value of an Mnode's list
int val(Mnode head)
{
    return head.list->value;
}

/*  performs a binary search on the path from the root to
    the leaf node. The function returns the index of the
    node where the value should be inserted.
*/
int binarySearch(Mnode *tree, int leaf, int depth, int value)
{
    int lo = 0, hi = depth - 1, mid, ans = leaf;
    int indexes[depth]; // stores the indexes of all Mnodes on the path from the root to the leaf node.
    for (int j = depth - 1; j >= 0; j--)
    {
        indexes[j] = leaf;
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

/*
    extracts (removes) the root element, which is the
    minimum element and returns it. It also allocates the
    next element in the list as the new list head and then
    calls the moundify function.
*/
int extractMin(Mnode *tree, int depth)
{

    // minimum value is stored in the root node's list first element
    int result = tree[0].list->value;
    Lnode *temp = tree[0].list;
    tree[0].list = temp->next;
    temp->next = NULL;
    tree[0].dirty = true;
    free(temp);

    // moundify the tree, starting from the root node
    moundify(tree, 0, depth);
    return result;
}

/*  moundify operation as described in the paper.
    The function 'moundifies' the tree from the
    given index until the property for
    mounidification is satisfied.
*/
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

// function for swapping two nodes
void swap(Mnode *tree, int l, int r)
{
    Mnode temp = tree[l];
    tree[l] = tree[r];
    tree[r] = temp;
}

Mnode *malloc_Mnode(int depth, Mnode *tree)
{
    tree = (Mnode *)malloc(10000000 * sizeof(Mnode));
    for (int i = 0; i < 10000000; i++)
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
