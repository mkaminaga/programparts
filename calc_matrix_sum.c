#include <stdio.h>

#define ROW 3
#define COLUMN 4

int main(){
    double a[ROW][COLUMN];
    double b[ROW][COLUMN];
    double c[ROW][COLUMN];
    int i=0;
    int j=0;

    printf("%d x %d set MATRIX A\n", ROW, COLUMN);

    for(i=0; i< ROW; i++){
        for(j=0; j<COLUMN; j++){
            printf("A[%d,%d]=", i+1, j+1);
	    scanf("%lf", &a[i][j]);
	}
    }

    printf("%d x %d set MATRIX B\n", ROW, COLUMN);

    for(i=0; i< ROW; i++){
        for(j=0; j<COLUMN; j++){
            printf("B[%d,%d]=", i+1, j+1);
	    scanf("%lf", &b[i][j]);
	}
    }

    for(i=0; i< ROW; i++){
        for(j=0; j<COLUMN; j++){
	    c[i][j] = a[i][j]+b[i][j];
            printf("C[%d,%d]=", i+1, j+1);
	    printf("%lf\n", c[i][j]);
	}
    }
}
