#include <stdio.h>

int main(int argc, char *argv[]) {
	FILE *fp;

	if (argc < 2) {
		printf("\nfile name is not specified!");
		return -1;
	}

	if ((fp = fopen(argv[1], "r")) == NULL) {
		printf("\nfailed to open %s", argv[1]);
	}
	printf("\n%s is successfully opened!", argv[1]);

	fclose(fp);

	return 0;
}
