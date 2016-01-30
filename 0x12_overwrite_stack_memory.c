#include <stdio.h>
#include <memory.h>
#include <string.h>

char* stack_mem_str();

int main(int argc, char* argv[]){
	char* p;
	p = stack_mem_str();
	printf("\nmain : %s", p);
	return(0);
}

char* stack_mem_str(){
	char work[5];// 4 + 1

	memset(work, 0x00, sizeof(work));
	memcpy(work, "TEST", 4);
	printf("\nstack_mem_str : %s", work);
	return(work);
}

/**
* なんか、例とちがうんだが、本来であればスタックメモリを
* printf文で書き換えられてしまうらしい (^^; ?
*/