#ifndef STACK_H_
#define STACK_H_

#define MAX_STACK_SIZE 1024

extern int stack[MAX_STACK_SIZE];
extern int stackPointer;

int pushToStack(int value);

int popFromStack();

#endif
