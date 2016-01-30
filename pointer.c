#include <stdio.h>

int main(int argc, char* argv[]){
	char data;
	char* lp_pointer;

	lp_pointer  = &data;
	*lp_pointer = 'A';
	printf("\n	lp_pointer = %c", *lp_pointer);
	printf("\n	data = %c", data);
	return(0);	
}