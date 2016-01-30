#include <stdio.h>

int main(int argc, char* argv[]){
	FILE* fp;
	char work[0x100];
	unsigned int line_num;
	if(argc < 2){
		printf("\nFile name is not specified!");
		return(-1);
	}
	fp = fopen(argv[1],"r");
	if(fp == NULL){
		printf("File was not found!");
		return(-1);
	}
	line_num = 1;
	while(fgets(work, sizeof(work), fp) != NULL){
		printf("%05d:%s", line_num, work);
		line_num++;
	}
	fclose(fp);
	return(0);
}