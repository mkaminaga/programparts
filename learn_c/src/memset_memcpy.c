#include <stdio.h>
#include <memory.h>
#include <string.h>

char* access_stack_mem();

int main(int argc, char* argv[]){
	char* p;
	p = access_stack_mem();
	printf("\nmain : %s", p);
	return(0);
}

char* access_stack_mem(){
	char str[5];

    /* set 5 bytes in str buffer */
	memset(str, 0x00, sizeof(str));

    /* copy 4 bytes to str buffer */
	memcpy(str, "TEST", 4);

	printf("\nstack_mem_str : %s", str);
	return(str);
}
