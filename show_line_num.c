#include <stdio.h>

int main(int argc, char* argv[]) {
	FILE* fp;
	char work[0x100];
	unsigned int line_num;

    /* file name not specified error */
	if (argc < 2) {
		printf("\nFile name is not specified!");
		return -1;
	}

    /* file open */
	if ((fp = fopen(argv[1],"r")) == NULL) {
		printf("File was not found!");
		return -1;
	}

    /* show file content */
	line_num = 1;
	while(fgets(work, sizeof(work), fp) != NULL) {
		printf("%05d:%s", line_num, work);
		line_num++;
	}

    /* file close */
	fclose(fp);

	return 0;
}
