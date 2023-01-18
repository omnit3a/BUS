#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <rpns/stack.h>
#include <math.h>

#define MAX_OPCODES 1024 * 10
#define MAX_OPCODE_SIZE 32
#define MAX_OPCODES_BUFFER_SIZE MAX_OPCODES * MAX_OPCODE_SIZE

#define DELIM " \n\t"

int tempA, tempB = 0;

int isNumber(char * text){
	int length = strnlen(text, MAX_OPCODE_SIZE);
	for (int i = 0 ; i < length ; i++){
		if (!isdigit(text[i])){
			return 0;
		}
	}
	return 1;
}

int main(int argc, char ** argv){
	if (argc < 2){
		fprintf(stderr, "rpns: must provide source file\n");
		return 1;
	}

	char filename[32];
	strcpy(filename, argv[1]);

	FILE * srcFile = fopen(filename, "r");

	if (srcFile == NULL){
		perror("rpns");
		return 1;
	}

	int tokenPos = 0;
	int tokensLength[MAX_OPCODES];
	int currentTokenLength;
	char * tokensList[MAX_OPCODE_SIZE];
	char * currentToken;
	char inputString[MAX_OPCODES_BUFFER_SIZE] = "";

	char tempCh;

	int loopReturn;
	int conditionMet;

	while ((tempCh = getc(srcFile)) != EOF){
		inputString[tokenPos++] = tempCh;
	}

	tokenPos = 0;

	currentToken = strtok(inputString, DELIM);
	while (currentToken){
		currentTokenLength = strlen(currentToken);
		tokensLength[tokenPos] = currentTokenLength;

		tokensList[tokenPos] = currentToken;
		tokenPos++;
		currentToken = strtok(NULL, DELIM);
	}

	int i = 0;
	int currentOp = 0;
	int tempPos = 0;
	for (i = 0 ; i < tokenPos ; i++){
		currentToken = tokensList[i];
		if (isNumber(currentToken)){
			pushToStack(atoi(currentToken));
		} else {
			if (strcmp(currentToken, "+") == 0){
				tempB = popFromStack();
				tempA = popFromStack();
				pushToStack(tempA+tempB);

			} else if (strcmp(currentToken, "-") == 0){
				tempB = popFromStack();
				tempA = popFromStack();
				pushToStack(tempA-tempB);
			
			} else if (strcmp(currentToken, "*") == 0){
				tempB = popFromStack();
				tempA = popFromStack();
				pushToStack(tempA*tempB);

			} else if (strcmp(currentToken, "/") == 0){
				tempB = popFromStack();
				tempA = popFromStack();
				pushToStack(tempA/tempB);
			
			} else if (strcmp(currentToken, "%") == 0){
				tempB = popFromStack();
				tempA = popFromStack();
				pushToStack(tempA%tempB);

			// duplicate value on top of stack
			} else if (strcmp(currentToken, "dup") == 0){
				duplicateOnStack();
			
			} else if (strcmp(currentToken, "sqrt") == 0){
				tempA = popFromStack();
				pushToStack(sqrt(tempA));


			} else if (strcmp(currentToken, "=") == 0){
				tempB = popFromStack();
				tempA = popFromStack();
				conditionMet = !(tempA == tempB);

			} else if (strcmp(currentToken, ">") == 0){
				tempB = popFromStack();
				tempA = popFromStack();
				conditionMet = (tempA > tempB);

			} else if (strcmp(currentToken, "<") == 0){
				tempB = popFromStack();
				tempA = popFromStack();
				conditionMet = (tempA < tempB);
			
			} else if (strcmp(currentToken, "!=") == 0){
				tempB = popFromStack();
				tempA = popFromStack();
				conditionMet = !(tempA != tempB);

			} else if (strcmp(currentToken, "if") == 0){
				if (conditionMet){
					while (strcmp(tokensList[i], "endif") != 0) {
						i++;
					}
					continue;
				}

			} else if (strcmp(currentToken, "while") == 0){
				loopReturn = i-1;
				if (conditionMet){
					while (strcmp(tokensList[i], "endloop") != 0) {
						i++;
					}
					continue;
				}
	
			} else if (strcmp(currentToken, "endloop") == 0){
				i = loopReturn;

			// output top stack value to terminal
			} else if (strcmp(currentToken, ".") == 0){
				tempA = popFromStack();
				printf("%d\n", tempA);
				pushToStack(tempA);
			
			} else if (strcmp(currentToken, "print") == 0){
				tempA = popFromStack();
				printf("%c",tempA);

			} else if (strcmp(currentToken, "swap") == 0){
				swapOnStack();

			} else if (strcmp(currentToken, "drop") == 0){
				tempA = popFromStack();
			
			} else if (strcmp(currentToken, "met") == 0){
				conditionMet = 1;
			
			} else if (strcmp(currentToken, "unmet") == 0){
				conditionMet = 0;

			} else {
				break;
			}
		}
	}
	

	fclose(srcFile);
	return 0;
}
