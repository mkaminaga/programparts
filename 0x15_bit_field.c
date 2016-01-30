#include <stdio.h>
#include <memory.h>

typedef struct ascii_code_bit_table_t{
	unsigned bit0 : 1;
	unsigned bit1 : 1;
	unsigned bit2 : 1;
	unsigned bit3 : 1;
	unsigned bit4 : 1;
	unsigned bit5 : 1;
	unsigned bit6 : 1;
	unsigned bit7 : 1;
} _ascii_code_bit_table;

void ascii_code_bit_view(unsigned char ascii_code);

int main(int argc, char* argv[]){
	char* str = "hello world!";
	do{
		ascii_code_bit_view(*str);
		str++;
	}while(*str != 0);
	return(0);
}

void ascii_code_bit_view(unsigned char ascii_code){
	_ascii_code_bit_table bit_table;
	memcpy(&bit_table, &ascii_code, sizeof(char));
	printf("\nchar : %c, hex : 0x%02x, bin > ", ascii_code, ascii_code);
	printf("%u", (bit_table.bit0) ? 0 : 1);
	printf("%u", (bit_table.bit1) ? 0 : 1);
	printf("%u", (bit_table.bit2) ? 0 : 1);
	printf("%u", (bit_table.bit3) ? 0 : 1);
	printf("%u", (bit_table.bit4) ? 0 : 1);
	printf("%u", (bit_table.bit5) ? 0 : 1);
	printf("%u", (bit_table.bit6) ? 0 : 1);
	printf("%u", (bit_table.bit7) ? 0 : 1);
}