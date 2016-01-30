#include <stdio.h>
#include <memory.h>
#include <malloc.h>

char* access_heep_mem();
char* g_heep_str = "hello!";

int main(int argc, char* argv[]) {
	char* p;

	p = access_heep_mem();
	if (p == NULL) {
		printf("\nFailed to alocate leep memory!");
		return(-1);
	}
	printf("\nmain : %s", p);

    /* release mem region by flee */
	free(p);
	return 0;
}

char* access_heep_mem() {
	char* str;

    /* get mem region by malloc */
	str = (char*) malloc(5);// 4 + 1
	if (str == NULL) return (char*) NULL;

    /* set cursor to memory */
	memset(str, 0x00, 5);

    /* write to memory */
	memcpy(str, "TEST", 4);

	printf("\naccess_heep_mem : %s", str);
	printf("\nglobal variable : %s", g_heep_str);

	return str;
}
