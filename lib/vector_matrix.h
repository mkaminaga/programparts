#ifndef VECTOR_MATRIX_H
#define VECTOR_MATRIX_H

/* add_matrix(double[], double[], double[], uint32_t, uint32_t)
 * arg1: matrix1 (A[i][j] = A[i * column + j])
 * arg2: matrix2 (B[i][j] = B[i * column + j])
 * arg3: solution matrix (X[i][j] = X[i * column + j])
 * arg4: number of row
 * arg5: number of column */
void add_matrix();

/* cross_vector(double[], double[], double[], uint32_t)
 * arg1: matrix1 (A[i][j] = A[i * column + j])
 * arg2: matrix2 (B[i][j] = B[i * column + j])
 * arg3: solution matrix (X[i][j] = X[i * column + j])
 * arg4: number of cordinates of vector */
void cross_vector(double a[], double b[], double x[], uint32_t vector_len);

/* dot_vector(double[], double[], double[])
 * arg1: matrix1 (A[i][j] = A[i * column + j])
 * arg2: matrix2 (B[i][j] = B[i * column + j])
 * arg3: solution matrix (X[i][j] = X[i * column + j]) */
double dot_vector(double a[], double b[], uint32_t row);

/* produce_matrix_vector_product(double[], double[], double[], uint32_t, uint32_t)
 * arg1: matrix (A[i][j] = A[i * column + j])
 * arg2: vector
 * arg3: number of row
 * arg4: number of column */
void produce_matrix_vector_product(
        double a[], double x[], double y[], uint32_t row, uint32_t column);

#endif /* VECTOR_MATRIX_H */
