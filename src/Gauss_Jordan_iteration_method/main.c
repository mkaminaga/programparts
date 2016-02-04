#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "../../lib/gauss_jordan_iteration_method.h"

#define SIZE 4

int main() {
    double x[SIZE] = {0};

    double a[SIZE * SIZE] = {
         2.0,  4.0, -4.0,  8.0,
         5.0,  8.0,  4.0, -2.0,
        -3.0, -6.0,  2.0,  1.0,
         6.0,  7.0, -1.0,  3.0
    };

    double b[SIZE] = {
         2.0,
        -1.0,
        13.0,
        -1.0
    };

    gauss_jordan_iteration(SIZE, a, b, x);

    /* show results */
    uint32_t i = 0;
    uint32_t j = 0;

    /* matrix */
    printf("A\n");
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++) printf("%15.2f", a[i * j]);
        printf("\n");
    }
    printf("\n");

    /* RS */
    printf("b\n");
    for(i = 0; i < SIZE; i++) printf("%15.5f", b[i]);
    printf("\n\n");

    /* answer */
    printf("x\n");
    for(i = 0; i < SIZE; i++) printf("%15.5f", x[i]);
    printf("\n");

    return 0;
}
