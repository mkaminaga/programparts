#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include "vector_matrix.h"
#include "power_method.h"

/* power(double[], double[], double[], double[], uint32_t)
 * arg1: cubic matrix (A[i][j] = A[i * cubic_matrix_size + j])
 * arg2: eigenvalue  (the largest one comes first)
 * arg3: eigenvector (coresponding to eigenvalue)
 * arg4: starting value of eigenvector, necessary for this algolithm
 * arg5: size of cubic matric */
void power_method(
        double a[], double n[], double x[], double ix[], uint32_t cubic_matrix_size) {

    double x_old[cubic_matrix_size];
    uint32_t i = 0;
    double r = 0;
    double r_new = 0;

    /* set  */
    for (i = 0; i < cubic_matrix_size; i++) x_old[i] = ix[i];

    /* set initial data */
    produce_matrix_vector_product(
        a, ix, x, cubic_matrix_size, cubic_matrix_size);
    r_new = rayliegh_quatient(a, x, cubic_matrix_size);
    r = 0.0;

    while(fabs(r - r_new) > 1E-6){

#if defined(DEBUG)
        /* show progress */
        printf("rayleigh quatient = %10.6lf\n", r_new);
#endif

        /* shift data */
        r = r_new;
        for(i = 0; i < cubic_matrix_size; i++){
            x_old[i] = x[i];
        }

        /* set new data */
        produce_matrix_vector_product(
            a, x_old, x, cubic_matrix_size, cubic_matrix_size);
        r_new = rayliegh_quatient(a, x, cubic_matrix_size);
    }

    /* store result */
    n[0] = r_new;
}

/* rayliegh_quatient(double[], double[], uint32_t)
 * arg1: matrix (A[i][j] = A[i * cubic_matrix_size + j])
 * arg2: vector
 * arg3: size of cubic matrix (A is (cubic_matrix_size, cubic_matrix_size) */
double rayliegh_quatient(double a[], double x[], uint32_t cubic_matrix_size){
    double value = 0;
    double y[cubic_matrix_size];

    produce_matrix_vector_product(
        a, x, y, cubic_matrix_size, cubic_matrix_size);
    value = dot_vector(y, x, cubic_matrix_size)
        / dot_vector(x, x, cubic_matrix_size);

    return value;
}

