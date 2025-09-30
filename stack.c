#include "stack.h"

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

int stackIsEmpty(Stack* s) {
    return s->Top == NULL;
};