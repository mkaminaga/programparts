#include <stdio.h>
#include <stdint.h>
#include "vector_matrix.h"

/* add_matrix(double[], double[], double[], uint32_t, uint32_t)
 * arg1: matrix1 (A[i][j] = A[i * column + j])
 * arg2: matrix2 (B[i][j] = B[i * column + j])
 * arg3: solution matrix (X[i][j] = X[i * column + j])
 * arg4: number of row
 * arg5: number of column */
void add_matrix(
        double a[], double b[], double x[], uint32_t row, uint32_t column) {
    for (uint32_t i = 0; i < row * column; i++) x[i] = a[i] + b[i];
}

/* cross_vector(double[], double[], double[], uint32_t)
 * arg1: matrix1 (A[i][j] = A[i * column + j])
 * arg2: matrix2 (B[i][j] = B[i * column + j])
 * arg3: solution matrix (X[i][j] = X[i * column + j])
 * arg4: number of cordinates of vector */
void cross_vector(double a[], double b[], double x[], uint32_t vector_len) {
    uint32_t i = 0;
    for(i = 0; i < vector_len; i++){
        x[i] = a[(i + 1) % vector_len] * b[(i + 2) % vector_len]
             - a[(i + 2) % vector_len] * b[(i + 1) % vector_len];
    }
}

/* dot_vector(double[], double[], double[])
 * arg1: matrix1 (A[i][j] = A[i * column + j])
 * arg2: matrix2 (B[i][j] = B[i * column + j])
 * arg3: solution matrix (X[i][j] = X[i * column + j]) */
double dot_vector(double a[], double b[], uint32_t row){
    uint32_t i = 0;
    double value = 0;

    for(i = 0; i < row; i++) value += a[i] * b[i];

    return value;
}

/* produce_matrix_vector_product(double[], double[], double[], uint32_t, uint32_t)
 * arg1: matrix (A[i][j] = A[i * column + j])
 * arg2: vector
 * arg3: number of row
 * arg4: number of column */
void produce_matrix_vector_product(
        double a[], double x[], double y[], uint32_t row, uint32_t column){
    uint32_t i = 0;
    uint32_t j = 0;

    for(i = 0; i < row; i++){
        y[i] = 0.0; //clear
        for(j = 0; j < column; j++) y[i] += a[i * column + j] * x[j];
    }
}
