#include "mnode.h";
#ifndef CONCURRENTPQ_H
#define CONCURRENTPQ_H


typedef struct 
{
    Mnode tree[];
} ConcurrentPQ;

ConcurrentPQ* createConcurrentPQ(int size, int numbers[]);
void insert(ConcurrentPQ* pq, int val);
int extractMin(ConcurrentPQ* pq);
#endif

