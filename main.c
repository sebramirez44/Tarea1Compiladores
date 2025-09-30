#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
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

void enqueue(Queue* q, int data) {
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

void dequeue(Queue* q) {
    if (q->first == NULL) {
        return;
    } else if (q->first->next != NULL) {
        Node* currentFront = q->first;
        q->first = q->first->next;
        free(currentFront);
    } else {
        free(q->first);
    }
    
};

typedef struct Stack {
    Node* front;
} Stack;

int main() {
    Queue* q = createQueue();
    enqueue(q, 10);
    enqueue(q, 20);
    dequeue(q);
    printf("%d", q->first->data);
    return 0;
};