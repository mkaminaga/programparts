#include <stdio.h>
#define COLUMN 3 

void cross(double* ans, double* x, double* y);

int main(){
	double a[COLUMN];
	double b[COLUMN];
	double c[COLUMN];
	int i=0;

	printf("Input 1*%d MATRIX A\n", COLUMN);
	for(i=0; i<COLUMN; i++){	
		printf("A[%d] =", i+1);
		scanf("%lf", &a[i]);
	}

	printf("Input 1*%d MATRIX B\n", COLUMN);
	for(i=0; i<COLUMN; i++){	
		printf("B[%d] =", i+1);
		scanf("%lf", &b[i]);
	}

    printf("A cross B:\n");
    cross(c, a, b);
   	for(i=0; i<COLUMN; i++){	
		printf("C[%d] = %lf\n", i+1, c[i]);
	}

    return 0;
}

void cross(double* c, double* a, double* b){
    int i=0;
    for(i=0; i<COLUMN;i++){
        c[i] = a[(i+1)%COLUMN]*b[(i+2)%COLUMN]
            - a[(i+2)%COLUMN]*b[(i+1)%COLUMN];
    }
}
