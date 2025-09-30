#include "queue.h"

typedef struct Node {
    void* data;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* first;
    Node* last;
} Queue;

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->first = NULL;
    q->last = NULL;

    return q;
}

void enqueue(Queue* q, void* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (q->first == NULL) {
        q->first = newNode;
        q->last = newNode;
    } else {
        // how current queue looks: q-> first != NULL
        q->last->next = newNode;
        q->last = newNode;
    }
};

void* dequeue(Queue* q) {
    void* currentFrontValue = NULL;
    if (q->first == NULL) {
        return currentFrontValue;
    } else if (q->first->next != NULL) {
        Node* currentFront = q->first;
        currentFrontValue = currentFront->data;
        q->first = q->first->next;
        free(currentFront);
        return currentFrontValue;
    } else {
        currentFrontValue = q->first->data;
        free(q->first);
        q->first = NULL;
        q->last = NULL;
        return currentFrontValue;
    }
};

void destroyQueue(Queue* q) {
    while (q->first != NULL) {
        dequeue(q);
    }
    free(q);
};

int queueIsEmpty(Queue* q) {
    return q->first == NULL;
};