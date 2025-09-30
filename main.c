#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* front;
} Queue;

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = NULL;

    return q;
}

void enqueue(Queue* q, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (q->front == NULL) {
        q->front = newNode;
    } else {
        newNode->next = q->front;
        q->front = newNode;
    }
};

void dequeue(Queue* q) {
    if (q->front == NULL) {
        return;
    } else {
        Node* currentFront = q->front;
        q->front = q->front->next;
        free(currentFront);
    }
};

int main() {
    Queue* q = createQueue();
    enqueue(q, 10);
    enqueue(q, 20);
    dequeue(q);
    printf("%d", q->front->data);
    return 0;
};