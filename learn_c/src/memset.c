#include <stdio.h>
#include <string.h>
#include <memory.h>

int main(int argc, char* argv[]){
	FILE* fp;
	long count;
	char* names[3] = {"Tanaka", "Yamada", "Megumi"};
	struct record_table_t {
		int record_num;
		char name[20];
	} record_table;

	fp = fopen("test_3-2.dat","wb");
	if(fp == NULL){
		printf("\nFailed to open file!");
		return(-1);
	}

	for(count = 0; count < 3; count++){
		memset(&record_table, 0x00, sizeof(record_table));
		record_table.record_num = count + 1;
		memcpy(record_table.name, names[count], strlen(names[count]));
		fwrite(&record_table, sizeof(record_table), 1, fp);
	}

	fclose(fp);
	return(0);
}