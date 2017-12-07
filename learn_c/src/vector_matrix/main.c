#include <stdio.h>
#include <stdint.h>
#include "../../lib/vector_matrix.h"

#define ROW 3
#define COLUMN 4

int main(){
    double a[ROW * COLUMN] = {
         1.0,  2.0,  3.0,  4.0,
         5.0,  6.0,  7.0,  8.0,
         9.0, 10.0, 11.0, 12.0,
    };
    double b[ROW * COLUMN] = {
         2.0,  3.0,  4.0,  5.0,
         6.0,  7.0,  8.0,  9.0,
        10.0, 11.0, 12.0, 13.0,
    };
    double c[ROW * COLUMN] = {0.0};
    double d[ROW] = {1.0, 2.0, 3.0};
    double e[ROW] = {2.0, 5.0, 7.0};
    double f[ROW] = {0.0};
    uint32_t i = 0;
    uint32_t j = 0;

    /*
     * test add_matrix
     * */

    /* show A */
    printf("A\n");
    for(i = 0; i < ROW; i++){
        for(j = 0; j < COLUMN; j++) printf("%15.5lf", a[i * COLUMN + j]);
        printf("\n");
    }
    printf("\n");

    /* show B */
    printf("B\n");
    for(i = 0; i < ROW; i++){
        for(j = 0; j < COLUMN; j++) printf("%15.5lf", b[i * COLUMN + j]);
        printf("\n");
    }
    printf("\n");

    /* calculate */
    add_matrix(a, b, c, ROW, COLUMN);

    /* show C */
    printf("C = A + B\n");
    for(i = 0; i < ROW; i++){
        for(j = 0; j < COLUMN; j++) printf("%15.5lf", c[i * COLUMN + j]);
        printf("\n");
    }
    printf("\n");

    /*
     * test dot_vector
     * */

    /* show D */
    printf("D\n");
	for(i = 0; i < ROW; i++) printf("%15.5lf", d[i]);
    printf("\n\n");

    /* show E */
    printf("E\n");
	for(i = 0; i < ROW; i++) printf("%15.5lf", e[i]);
    printf("\n\n");

    /* calculate & show result */
    printf("x = D dot E\n");
    printf("%15.5lf",dot_vector(d, e, ROW));
    printf("\n\n");

    /*
     * test cross_vector
     * */

    /* show D */
    printf("D\n");
	for(i = 0; i < ROW; i++) printf("%15.5lf", d[i]);
    printf("\n\n");

    /* show E */
    printf("E\n");
	for(i = 0; i < ROW; i++) printf("%15.5lf", e[i]);
    printf("\n\n");

    /* calculate */
    cross_vector(d, e, f, ROW);

    /* show F */
    printf("F = D x E\n");
	for(i = 0; i < ROW; i++) printf("%15.5lf", f[i]);
    printf("\n");

    return 0;
}
