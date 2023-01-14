#include <stdio.h>

int main(int argc, char ** argv){
	if (argc == 1){
		fprintf(stderr, "newf: must provide filename\n");
		return 1;
	}

	FILE * tempFile;
	int tempArgc = argc;

	while (tempArgc-- != 1){
		tempFile = fopen(argv[tempArgc], "w");
		fclose(tempFile);
	}
	return 0;
}
