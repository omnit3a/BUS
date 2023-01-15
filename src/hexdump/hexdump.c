#include <stdio.h>
#include <string.h>

#define TEXT_DUMP_FLAG "-tx"
#define OCTAL_DUMP_FLAG "-oc" 

int main(int argc, char ** argv){
	
	char * filename;

	int foundTxFlag = 0;
	int foundOcFlag = 0;

	if (argc <= 1){
		fprintf(stderr, "read: must provide filename\n");
		return 1;
	} else if (argc > 1 && argc < 4){
		
		if (argc == 3){
			for (int i = 1 ; i < argc+1 ; i++){
				if (strcmp(argv[i], TEXT_DUMP_FLAG) == 0){
					foundTxFlag = 1;
				} else if (strcmp(argv[i], OCTAL_DUMP_FLAG) == 0){
					foundOcFlag = 1;
				} else {
					filename = argv[i];
				}
				if (i == 2){
					break;
				}
			}
		} else {
			filename = argv[1];
		}

	}

	FILE * tempFile;
	char tempCh;
	
	if (filename){
		tempFile = fopen(filename, "r");
	}

	if (tempFile){
		while ((tempCh = getc(tempFile)) != EOF){
			if (foundTxFlag){
				printf("%c",tempCh);
			} else if (foundOcFlag){
				printf("%o ",tempCh);
			} else {
				if (tempCh < 0x10){
					printf("0");
				}
				printf("%X ",tempCh);
			}
		}
		if (!foundTxFlag){
			printf("\n");
		}
		fclose(tempFile);
	} else {
		perror("hexdump");
	}
	return 0;
}
