#include <stdio.h>
#include <rpns/stack.h>

int stack[MAX_STACK_SIZE];
int stackPointer = 0;

int pushToStack(int value){
	stack[stackPointer++ % MAX_STACK_SIZE] = value;
	return 0;
}

int popFromStack(){
	return stack[--stackPointer % MAX_STACK_SIZE];
}
