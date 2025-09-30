#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    void* data;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* first;
    Node* last;
} Queue;

Queue* createQueue();
void enqueue(Queue* q, void* data);
void dequeue(Queue* q);
void destroyQueue(Queue* q);


#endif