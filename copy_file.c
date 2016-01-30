#include <stdio.h>

int main(int args, char* argv[]) {
	FILE* fp;
	FILE* fp_save;
	char work[0x100];

	if (args < 3) {
		printf("File name is not specified");
		return(-1);
	}

	if ((fp = fopen(argv[1], "r")) == NULL) {
		printf("\nFailed to open %s!", argv[1]);
		return(-1);
	}

	if ((fp_save = fopen(argv[2], "w")) == NULL) {
		printf("\nFailed to open %s!", argv[2]);
		fclose(fp);
		return(-1);
	}

	while(fgets(work, sizeof(work), fp) != NULL) {
		fprintf(fp_save, "%s", work);

        /* flush unwritten buffer */
		fflush(fp_save);
	}

	fclose(fp);
	fclose(fp_save);

	return 0;
}
