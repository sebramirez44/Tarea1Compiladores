#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

typedef struct StackNode StackNode;
typedef struct Stack Stack;

Stack* createStack();
void* stackPop(Stack* s);
void stackPush(Stack* s, void* data);
void destroyStack(Stack* s);
int stackIsEmpty(Stack* s);

#endif