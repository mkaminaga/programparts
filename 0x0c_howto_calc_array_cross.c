#include <stdio.h>

#define NUM_N 3 
#define NUM_L 4
#define NUM_M 5

int main(){
		double a[NUM_N][NUM_L];
		double b[NUM_L][NUM_M];
		double c[NUM_N][NUM_M];

		int i=0;
        int j=0;
        int k=0;

		printf("Input %d*%d MATRIX A\n", NUM_N, NUM_L);
		for(i=0; i<NUM_N; i++){	
            for(j=0; j<NUM_L; j++){
				printf("A[%d][%d] =", i+1, j+1);
				scanf("%lf", &a[i][j]);
            }

		}

    	printf("Input %d*%d MATRIX B\n", NUM_L, NUM_M);
		for(i=0; i<NUM_L; i++){	
            for(j=0; j<NUM_M; j++){
				printf("B[%d][%d] =", i+1, j+1);
				scanf("%lf", &b[i][j]);
            }
		}
        
        printf("A cross B:\n");
		for(i=0; i<NUM_N; i++){	
            for(j=0; j<NUM_M; j++){
                c[i][j] = 0;
                for(k=0; k<NUM_L; k++){
                    c[i][j] += a[i][k] * b[k][j];
                }
				printf("C[%d][%d] = %lf\n", i+1, j+1, c[i][j]);
            }
		}
}
