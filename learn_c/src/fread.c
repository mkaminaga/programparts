#include <stdio.h>

int main(int argc, char* argv[]) {

	struct record_table_t {
		int record_num;
		char name[20];
	} record_table;
	FILE* fp;
	char* names[3] = {"sir1", "sir2", "sir3"};

	fp = fopen("test_data.dat", "rb");
	if (fp == NULL) {
		printf("\nFailed to open file!");
		return -1;
	}

	while (fread(&record_table, sizeof(record_table), 1, fp) != 0) {
		printf("\nrecord_num  = %u, name = %s",
			record_table.record_num, record_table.name);
	}

	fclose(fp);
	return(0);
}
