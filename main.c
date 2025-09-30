#include <stdio.h>
#include <stdlib.h>

#include "queue.h"


int main() {
    Queue* q = createQueue();
    int* num1 = malloc(sizeof(int));
    *num1 = 10;
    int* num2 = malloc(sizeof(int));
    *num2 = 20;
    enqueue(q, num1);
    enqueue(q, num2);
    dequeue(q);
    printf("%d", *(int*)q->first->data);
    return 0;
};