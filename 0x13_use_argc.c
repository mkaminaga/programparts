#include <stdio.h>

int main(int argc, char *argv[]){
	if(argc < 2){
		printf("\nThere's no argument!!");
		return -1;
	}
	printf("\nArgument string > %s", argv[1]);
	return 0;
}