#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "../../lib/gauss_jordan_iteration_method.h"

#define N 4

int main() {
    double x[N] = {0};

    double a[N * N] = {
         2.0,  4.0, -4.0,  8.0,
         5.0,  8.0,  4.0, -2.0,
        -3.0, -6.0,  2.0,  1.0,
         6.0,  7.0, -1.0,  3.0
    };

    double b[N] = {
         2.0,
        -1.0,
        13.0,
        -1.0
    };

    gauss_jordan_iteration(N, a, b, x);

    /* show results */
    uint32_t i = 0;
    uint32_t j = 0;

    /* matrix */
    printf("A\n");
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++) printf("%15.2f", a[i * j]);
        printf("\n");
    }
    printf("\n");

    /* RS */
    printf("b\n");
    for(i = 0; i < N; i++) printf("%15.5f", b[i]);
    printf("\n\n");

    /* answer */
    printf("x\n");
    for(i = 0; i < N; i++) printf("%15.5f", x[i]);
    printf("\n");

    return 0;
}
