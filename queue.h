#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
typedef struct Queue Queue;

Queue* createQueue();
void* dequeue(Queue* q);
void enqueue(Queue* q, void* data);
void destroyQueue(Queue* q);


#endif