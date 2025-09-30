#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
typedef struct StackNode {
    void* data;
    struct StackNode* next;
} StackNode;

typedef struct Stack {
    StackNode* Top;
} Stack;

Stack* createStack() {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->Top = NULL;

    return s;
};

void stackPush(Stack* s, void* data) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->data = data;

    newNode->next = s->Top;
    s->Top = newNode;
};

void* stackPop(Stack* s) {
    if (s == NULL || s->Top == NULL) {
        return NULL;
    }
    StackNode* currTop = s->Top;
    void* currTopValue = currTop->data;
    s->Top = s->Top->next;
    free(currTop);

    return currTopValue;
};

void destroyStack(Stack* s) {
    while (s->Top != NULL) {
        stackPop(s);
    }
    free(s);
};

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