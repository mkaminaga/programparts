#include <stdio.h>
#include <memory.h>
#include <malloc.h>

char* heep_mem_str();
char* heep_str = "hello!";

int main(int argc, char* argv[]){
	char* p;

	p = heep_mem_str();
	if(p == NULL){
		printf("\nFailed to alocate leep memory!");
		return(-1);
	}
	printf("\nmain : %s", p);
	
	free(p); /* don't foreget this line. */
	return(0);
}

char* heep_mem_str(){
	char* work;

	work = (char*)malloc(5);// 4 + 1
	if(work == NULL){
		return((char*) NULL);
	}
	memset(work, 0x00, 5);
	memcpy(work, "TEST", 4);
	printf("\nheep_mem_str : %s",work);

	/* just, accessing to a global variable */
	printf("\nglobal variable : %s", heep_str);

	return(work);
}