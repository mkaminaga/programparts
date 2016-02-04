#ifndef GAUSS_JORDAN_ITERATION_METHOD_H
#define GAUSS_JORDAN_ITERATION_METHOD_H

/* gauss_jordan_iteration(uint32_t, double, double, double)
 * arg1: Square matrix row (column) size
 * arg2: Coefficient matrix (A[i][j] = arg2[i * size + j])
 * arg3: RS matrix
 * arg4: Solution matrix */
void gauss_jordan_iteration(uint32_t size, double a_p[], double b_p[], double x_p[]);

#endif /* GAUSS_JORDAN_ITERATION_METHOD_H */
