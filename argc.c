#include <stdio.h>

int main(int argc, char *argv[]){

    /* argc is not set */
	if(argc < 2){
		printf("\nThere's no argument!!");
		return -1;
	}

    /* argc is set */
	printf("\nArgument string > %s", argv[1]);
	return 0;
}
