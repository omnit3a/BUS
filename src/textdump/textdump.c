#include <stdio.h>

int main(int argc, char ** argv){
	if (argc == 1){
		fprintf(stderr, "read: must provide filename\n");
		return 1;
	}

	FILE * tempFile;
	char tempCh;

	tempFile = fopen(argv[1], "r");
	
	if (tempFile){
		while ((tempCh = getc(tempFile)) != EOF){
			printf("%c",tempCh);
		}
		fclose(tempFile);
	} else {
		perror("textdump");
	}
	return 0;
}
