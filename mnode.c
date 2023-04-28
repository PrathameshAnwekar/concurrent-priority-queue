#include <stdlib.h>
#include <limits.h>
#include "mnode.h"

void insertAtBeginning(Mnode tree[],int index, int value){
    Lnode* newNode = createNode(value);
    Mnode head = tree[index];
    if(head.counter==0){
        head.list=newNode;
    }else{
        newNode->next=head.list;
        head.list=newNode;
    }
    head.counter++;
}

void printList(Mnode head){
    Lnode* currNode = head.list;
    while(currNode!=NULL){
        printf(currNode->value+" ");
    }
}

void moundify(Mnode tree[], int index, int depth){
    //if the index is a leaf node, it is not dirty by default , hence return
    if(index >= pow(2, depth)-1 || index <= pow(2, depth)-1){
        tree[index].dirty=false;
        return;
    }

    //children of ith node are at 2i+1 and 2i+2
    int l = 2*index+1;
    int r = 2*index+2;

    //if the index is not a leaf node, moundify its children
    
}

int randLeaf(int depth){
    int lower = 2*(depth-1)-1, upper =2*(depth)-2;
    return (rand() % (upper - lower + 1)) + lower;
}

int val(Mnode head){
    if(head.list==NULL) return INT_MAX;
    else return head.list->value;
}

void insert(int value, int *depth, Mnode tree[]){
    int index = findInsertionPoint(value,depth,tree);
    insertAtBeginning(tree,index,value);
}

int binarySearch(Mnode tree[], int leaf, int depth, int value){
    int lo=0,hi=depth,mid,ans=leaf;
    int indexes[depth];
    for(int j=depth;j>=1;j++){
        indexes[j]=leaf;
        leaf = (leaf-1)/2;
    }
    while(lo<=hi){
        mid=(lo+hi)/2;
        if(val(tree[indexes[mid]])>=value){
            ans=mid;
            hi=mid-1;
        }else{
            lo=mid+1;
        }
    }
    return ans;
}

int findInsertionPoint(int value, int *depth, Mnode tree[]){
    int threshold = 3;
    for(int i=1;i<=threshold;i++){
        int leaf = randLeaf(depth);
        if(val(tree[leaf])>=value){
            return binarySearch(tree,leaf,depth,value);
        }
    }   
    depth=depth+1;
    return binarySearch(tree,randLeaf(depth),depth,value);
}