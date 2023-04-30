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
void insertAtBeginning(Mnode *tree, int index, int value);
void printList(Mnode head);
void insert(int value, int *depth, Mnode *tree);
int randLeaf(int depth);
int val(Mnode head);
int findInsertionPoint(int value, int *depth, Mnode *tree);
int extractMin(Mnode *tree, int depth);
void moundify(Mnode *tree, int index, int depth);
void swap(Mnode *tree, int l, int r);
Mnode *realloc_Mnode(int depth, Mnode *tree);

int MAX_NUMBERS = 100;

int main()
{
    int depth = 1;
    int numbers[MAX_NUMBERS];
    int count = readData(numbers);
    Mnode *tree;
    tree = realloc_Mnode(depth, tree);
    printf("The value of tree[0] is currently %d\n", tree[0].list->value);
    for (int i = 0; i < count; i++)
    {
        insert(numbers[i], &depth, tree);
        printf("\n\n\n\n\n\n");
    }

    printf("this is the min %d\n", extractMin(tree, depth));

    return 0;
}

int readData(int numbers[])
{
    FILE *fp;

    int count = 0;
    int number = 0;
    fp = fopen("data.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }

    while (fscanf(fp, "%d", &number) != EOF)
    {
        // Store the integer in the array
        if (count >= MAX_NUMBERS)
        {
            printf("Too many numbers in file\n");
            return 1;
        }
        numbers[count] = number;
        count++;
    }

    fclose(fp);

    printf("The integers are: ");
    for (int i = 0; i < count; i++)
    {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    return count;
}

Lnode *createNode(int value)
{
    printf("trying to return new node \n");
    Lnode *newnode = (Lnode *)malloc(sizeof(Lnode));
    newnode->value = value;
    newnode->next = NULL;
    printf("returning new lnode\n");
    return newnode;
}

void insertAtBeginning(Mnode *tree, int index, int value)
{
    printf("Insert at beginning \n");
    Lnode *newNode = createNode(value);
    printf("created new node \n");

    if (tree[index].counter == 0)
    {
        tree[index].list = newNode;
    }
    else
    {
        newNode->next = tree[index].list;
        tree[index].list = newNode;
    }
    tree[index].counter++;
    printf("inserted %d at index %d \n", value, index);
}

// void printList(Mnode head)
// {
//     Lnode *currNode = head.list;
//     while (currNode != NULL)
//     {
//         printf(currNode->value + " ");
//     }
// }

void moundify(Mnode *tree, int index, const int depth)
{
    // if the index is a leaf node, it is not dirty by default , hence return
    printf("calling moundify \n");
    if (index >= (int)pow(2, depth - 1) - 1 || index <= (int)pow(2, depth) - 2)
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
        printf("moundified \n");
        return;
    }
}

int randLeaf(int depth)
{
    printf("Called rand leaf at depth %d\n", depth);
    if (depth == 1)
        return 0;
    int lower = (int)pow(2, depth - 1) - 1, upper = (int)pow(2, depth) - 2;
    int random = (rand() % (upper - lower + 1)) + lower;
    printf("random number generated is %d \n", random);
    return random;
}

int val(Mnode head)
{
    printf("Finding the val function \n");
    if (head.list == NULL)
        return INT_MAX;
    else
        return head.list->value;
}

void insert(int value, int *depth, Mnode *tree)
{
    printf("Called insert function\n");
    int index = findInsertionPoint(value, depth, tree);
    printf("Insertion point found at %d \n", index);
    insertAtBeginning(tree, index, value);
}

int binarySearch(Mnode *tree, int leaf, int depth, int value)
{
    printf("Called binary search \n");
    int lo = 0, hi = depth, mid, ans = leaf;
    int indexes[depth];
    for (int j = depth; j >= 1; j--)
    {
        indexes[j - 1] = leaf;
        leaf = (leaf - 1) / 2;
    }
    while (lo <= hi)
    {
        mid = (lo + hi) / 2;
        if (val(tree[indexes[mid]]) >= value)
        {
            ans = mid;
            hi = mid - 1;
        }
        else
        {
            lo = mid + 1;
        }
    }
    printf("Binary search returning %d \n", ans);
    return ans;
}

int findInsertionPoint(int value, int *depth, Mnode *tree)
{
    printf("Finding the insertion point\n");
    int threshold = 3;
    for (int i = 1; i <= threshold; i++)
    {
        int leaf = randLeaf(*depth);
        printf("Found the rand leaf as %d \n", leaf);
        printf("The value of tree[val] is %d \n", tree[leaf].list->value);
        if (val(tree[leaf]) >= value)
        {
            return binarySearch(tree, leaf, *depth, value);
        }
    }
    *depth = *depth + 1;
    tree = realloc_Mnode(*depth, tree);
    return binarySearch(tree, randLeaf(*depth), *depth, value);
}

int extractMin(Mnode *tree, int depth)
{
    printf("Extracting min \n");
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
    printf("Extracted min \n");
    return result;
}

// function for swapping any two nodes
void swap(Mnode *tree, int l, int r)
{
    Mnode temp = tree[l];
    tree[l] = tree[r];
    tree[r] = temp;
    printf("swap successful \n");
}

Mnode *realloc_Mnode(int depth, Mnode *tree)
{
    printf("Reallocating tree \n");
    tree = (Mnode *)realloc(tree, ((int)pow(2, depth) - 1) * sizeof(Mnode));
    for (int i = (int)pow(2, depth - 1) - 1; i < (int)pow(2, depth) - 1; i++)
    {
        tree[i].dirty = false;
        tree[i].counter = 0;
        tree[i].list = createNode(INT_MAX);
        printf("initialised node %d \n", i);
    }
    printf("The value of tree[0] is currently inside realloc %d\n", tree[0].list->value);
    printf("Realloc successful, size of new tree is %d nodes for depth=%d \n", ((int)pow(2, depth) - 1), depth);
    return tree;
}
