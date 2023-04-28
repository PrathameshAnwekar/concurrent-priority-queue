#include <stdlib.h>
#include "mnode.h"

void insertAtBeginning(Mnode head, int value){
    Lnode* newNode = createNode(value);
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