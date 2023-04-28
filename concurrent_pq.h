#ifndef CONCURRENTPQ_H
#define CONCURRENTPQ_H

#include "mnode.h";

typedef struct
{
    Mnode tree[];
} ConcurrentPQ;

ConcurrentPQ *createConcurrentPQ(int size, int numbers[]);
void insert(ConcurrentPQ pq[], int value);
int extractMin(ConcurrentPQ pq[]);
void moundify(ConcurrentPQ pq[], int index);
#endif
