#include <stdio.h>
#include <memory.h>

typedef struct bit_table{
	unsigned bit0 : 1;
	unsigned bit1 : 1;
	unsigned bit2 : 1;
	unsigned bit3 : 1;
	unsigned bit4 : 1;
	unsigned bit5 : 1;
	unsigned bit6 : 1;
	unsigned bit7 : 1;
} _bit_table;

void bit_view(unsigned char ascii);

int main(int argc, char* argv[]){
	char* str = "hello world!";
	do {
		bit_view(*str);
		str++;
	} while (*str != 0);
	return 0;
}

void bit_view(unsigned char ascii) {
	_bit_table bit_table;
	memcpy(&bit_table, &ascii, sizeof(char));

	printf("\nchar:%c, hex:0x%02x, bin > ", ascii, ascii);
	printf("%u", (bit_table.bit0) ? 0 : 1);
	printf("%u", (bit_table.bit1) ? 0 : 1);
	printf("%u", (bit_table.bit2) ? 0 : 1);
	printf("%u", (bit_table.bit3) ? 0 : 1);
	printf("%u", (bit_table.bit4) ? 0 : 1);
	printf("%u", (bit_table.bit5) ? 0 : 1);
	printf("%u", (bit_table.bit6) ? 0 : 1);
	printf("%u", (bit_table.bit7) ? 0 : 1);
}
