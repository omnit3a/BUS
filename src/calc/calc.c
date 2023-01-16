#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX_OPCODE_BUFFER_SIZE 1024 
#define MAX_STACK_SIZE 256
#define DELIM " "

int stack[MAX_STACK_SIZE];
int stackPointer = 0;

int pushToStack(int value){
	stack[stackPointer++ % MAX_STACK_SIZE] = value;
}

int popFromStack(){
	return stack[--stackPointer % MAX_STACK_SIZE];
}

int isNumber(char * text){
	int length = strnlen(text,256);
	for (int i = 0 ; i < length ; i++){
		if (!isdigit(text[i])){
			return 0;
		}
	}
	return 1;
}

int main(int argc, char ** argv){
	if (argc < 3){
		fprintf(stderr, "calc: must provide at least 2 tokens\n");
		return 1;	
	}

	int tokenPos = 0;
	int tokensLength[MAX_OPCODE_BUFFER_SIZE];
	int lengthOfCurrentToken;
	char * tokensList[256];
	char * currentToken;
	char inputString[MAX_OPCODE_BUFFER_SIZE] = "";

	char tempIntString[256];
	int tempA;
	int tempB;

	// group all tokens into one string
	for (int i = 1 ; i < argc ; i++){
		strcat(inputString, argv[i]);
		strcat(inputString, " ");
	}

	// tokenize parameters
	currentToken = strtok(inputString, DELIM);
	while (currentToken){
		lengthOfCurrentToken = strlen(currentToken);
		tokensLength[tokenPos] = lengthOfCurrentToken;

		tokensList[tokenPos] = currentToken;
		tokenPos++;
		currentToken = strtok(NULL, DELIM);
	}

	for (int i = 0 ; i < tokenPos ; i++){
		if (isNumber(tokensList[i])){
			pushToStack(atoi(tokensList[i]));
		} else {
			if (strcmp(tokensList[i], "+") == 0){
				tempB = popFromStack();
				tempA = popFromStack();
				printf("%d\n",tempA+tempB);
				pushToStack(tempA+tempB);

			} else if (strcmp(tokensList[i], "-") == 0){
				tempB = popFromStack();
				tempA = popFromStack();
				printf("%d\n",tempA-tempB);
				pushToStack(tempA-tempB);

			} else if (strcmp(tokensList[i], "x") == 0){
				tempA = popFromStack();
				tempB = popFromStack();
				printf("%d\n",tempA*tempB);
				pushToStack(tempA*tempB);

			} else if (strcmp(tokensList[i], "/") == 0){
				tempB = popFromStack();
				tempA = popFromStack();
				printf("%d\n",tempA/tempB);
				pushToStack(tempA/tempB);

			} else if (strcmp(tokensList[i], "%") == 0){
				tempB = popFromStack();
				tempA = popFromStack();
				printf("%d\n",tempA%tempB);
				pushToStack(tempA%tempB);

			} else if (strcmp(tokensList[i], "sqrt") == 0){
				tempA = popFromStack();
				printf("%d\n",(int)sqrt(tempA));
				pushToStack((int)sqrt(tempA));
			
			} else if (strcmp(tokensList[i], "sqr") == 0){
				tempA = popFromStack();
				printf("%d\n",tempA*tempA);
				pushToStack(tempA*tempA);
			} else {
				break;
			}
		}
	}
	return 0;
}
