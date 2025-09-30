#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "stack.h"


int main() {
    Queue* q = createQueue();
    int* num1 = malloc(sizeof(int));
    *num1 = 10;
    int* num2 = malloc(sizeof(int));
    *num2 = 20;
    enqueue(q, num1);
    enqueue(q, num2);
    int* res= (int*)dequeue(q);
    printf("%d\n\n", *res);

    Stack* s = createStack();
    int* num3 = malloc(sizeof(int));
    *num3 = 30;
    int* num4 = malloc(sizeof(int));
    *num4 = 40;
    stackPush(s, num3);
    stackPush(s, num4);
    int* res2 = (int*)stackPop(s);
    printf("%d", *res2);

    return 0;
};