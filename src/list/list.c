#include <stdio.h>
#include <string.h>
#include <dirent.h>

#define FILE_COLOR "\e[1;34m"
#define DIRECTORY_COLOR "\e[1;36m"
#define RESET_COLOR "\e[0m"

int main(int argc, char ** argv){
	DIR * workingDirectory;
	struct dirent * printableDirectory;

	switch (argc){
		case 1:
			workingDirectory = opendir(".");
			break;
		case 2:
			workingDirectory = opendir(argv[1]);
			break;
		default:
			fprintf(stderr, "list: only one directory may be listed at a time\n");
			return 1;
	}
	
	char * fileToPrint;

	if (workingDirectory){
		while ((printableDirectory = readdir(workingDirectory)) != NULL){
			fileToPrint = printableDirectory->d_name;

			// do not print relational files
			if (strcmp(fileToPrint, "..") == 0){
				continue;
			} else if (strcmp(fileToPrint,".") == 0){
				continue;
			}

			// set color of file depending on type
			switch(printableDirectory->d_type){
				case DT_REG:
					printf("%s",FILE_COLOR);
					break;
				case DT_DIR:
					printf("%s",DIRECTORY_COLOR);
					break;
				default:
					printf("%s",RESET_COLOR);
					break;
			}
			
			// print base filename
			printf("%s\n", fileToPrint);
		}
		closedir(workingDirectory);
	}
	printf("%s",RESET_COLOR);
	return 0;
}
