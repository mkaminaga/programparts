#include <stdio.h>

int main(int argc, char* argv[]){
	char* str = "hello world!";
	char ascii_code;

	ascii_code = *str;
	do{
		printf("\n%c = 0x%02x", ascii_code, ascii_code);
		str++;
		ascii_code = *str;
	}while(ascii_code != 0);
	
	return(0);
}