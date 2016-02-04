#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "../../lib/power_method.h"

#define CUBIC_MATRIX_SIZE  3

int main(int argc, char* argv[]){
    double a[CUBIC_MATRIX_SIZE * CUBIC_MATRIX_SIZE] = {
             4,  -4,   0,
            -4,   8,  -4,
             0,  -4,   4
    };
    double x[CUBIC_MATRIX_SIZE] = {0.0};
    double ix[CUBIC_MATRIX_SIZE] = {0.2, 0.3, 0.6};
    double n[1];

    /* calculate */
    power_method(a, n, x, ix, CUBIC_MATRIX_SIZE);

    /* show final result */
    printf("largest eigenvalue: %10.5lf\n", n[0]);

    return 0;
}
