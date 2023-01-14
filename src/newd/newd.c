#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char ** argv){
	if (argc == 1){
		fprintf(stderr, "newd: must provide filename\n");
		return 1;
	}

	int check;
	int tempArgc = argc;

	while (tempArgc-- != 1){
		if (mkdir(argv[tempArgc], 0777) != 0){
			perror("newd");
			return 1;
		}
	}
	return 0;
}
