#include <stdio.h>
#include <stdint.h>

int main(int argc, char* argv[]){
	char* str = "hello world!";
	char ascii;

	ascii = *str;
	do {
		printf("\n%c:0x%02x", ascii, ascii);
		str++;
		ascii= *str;
	} while (ascii != '\0');

	return 0;
}
