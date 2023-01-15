#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#define FILE_COLOR "\e[1;34m"
#define DIRECTORY_COLOR "\e[1;36m"
#define RESET_COLOR "\e[0m"

#define EXTRA_INFO_FLAG "-ex"

int main(int argc, char ** argv){
	DIR * workingDirectory;
	struct dirent * printableDirectory;
	char * dirName;

	int foundExFlag = 0;

	if (argc <= 1){
		workingDirectory = opendir(".");
	} else if (argc > 1 && argc < 4 ){
		
		if (argc == 3){
			for (int i = 1 ; i < argc+1 ; i++){
				if (strcmp(argv[i],EXTRA_INFO_FLAG) == 0){
					foundExFlag = 1;
				} else {
					workingDirectory = opendir(argv[i]);
					dirName = argv[i];
				}
				if (i == 2){
					break;
				}
			}
		} else {
			workingDirectory = opendir(argv[1]);
			dirName = argv[1];
		}
	}
	
	char * fileToPrint;
	int row = 1;

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
			if (!foundExFlag){
				printf("%s    ", fileToPrint);
				if (row++ % 10 == 0){
					printf("\n");
				}	
			} else {
				if (chdir(dirName) == 0){

					// print file permissions
					// print read permission
					if (access(fileToPrint,R_OK) == 0){
						printf("r");
					} else {
						printf("-");
					}
					// print write permission
					if (access(fileToPrint,W_OK) == 0){
						printf("w");
					} else {
						printf("-");
					}
					// print executable permission
					if (access(fileToPrint,X_OK) == 0){
						printf("x	");
					} else {
						printf("-	");
					}

					printf("%s\n", fileToPrint);

				} else {
					perror("list");
					return 1;
				}
			}
		}
		closedir(workingDirectory);
	}
	printf("%s\n",RESET_COLOR);
	return 0;
}
