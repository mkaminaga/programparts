#include <stdio.h>
#include <stdint.h>
#include "gauss_jordan_iteration.h"

/* gauss_jordan_iteration(uint32_t, double, double, double)
 * arg1: Square matrix row (column) size
 * arg2: Coefficient matrix (A[i][j] = arg2[i * size + j])
 * arg3: RS matrix
 * arg4: Solution matrix */
void gauss_jordan_iteration(
        uint32_t size, double a_p[], double b_p[], double x_p[]){
    double a[size * size];
    double b[size];

    int i = 0;
    int j = 0;
    int k = 0;
    double p = 0;

    /* copy argument value */
    for(i = 0; i < size * size; i++) a[i] = a_p[i];
    for(i = 0; i < size; i++) b[i] = b_p[i];

    /* zennshin shoukyo */
    for(i = 0; i < size - 1; i++){
        /* pivotting */
        //pivotting(a, b, i);

        for(j = i + 1; j < size; j++){
            /* pivot */
            p = a[j * size + i] / a[i * size + i];

            /* eliminate LS */
            for(k = i; k < size; k++)
                a[j * size + k] = a[j * size + k] - p * a[i * size + k];

            /* eliminate RS */
            b[j] = b[j] - p * b[i];
        }
    }

    /* koutai dainyuu */
    for(i = size - 1; i >= 0; i--){
        x_p[i] = b[i] / a[i * size + i];

        for(j = i + 1; j < size; j++){
            x_p[i] = x_p[i] - (a[i * size + j] / a[i * size + i]) * x_p[j];
        }
    }
}
