#include <stdio.h>

int main(int argc, char ** argv){
	if (argc == 1){
		fprintf(stderr, "remf: must provide filename\n");
		return 1;
	}

	int tempArgc = argc;

	while (tempArgc-- != 1){
		if (remove(argv[tempArgc])){
			perror("remf");
		}
	}
	return 0;
}
