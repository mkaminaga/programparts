#ifndef POWER_METHOD_H
#define POWER_METHOD_H

/* power_method(double[], double[], double[], double[], uint32_t)
 * arg1: cubic matrix (A[i][j] = A[i * cubic_matrix_size + j])
 * arg2: eigenvalue  (the largest one comes first)
 * arg3: eigenvector (coresponding to eigenvalue)
 * arg4: starting value of eigenvector, necessary for this algolithm
 * arg5: size of cubic matric */
void power_method( double a[], double n[], double x[], double ix[], uint32_t cubic_matrix_size);

/* rayliegh_quatient(double[], double[], uint32_t)
 * arg1: matrix (A[i][j] = A[i * cubic_matrix_size + j])
 * arg2: vector
 * arg3: size of cubic matrix (A is (cubic_matrix_size, cubic_matrix_size) */
double rayliegh_quatient(double a[], double x[], uint32_t cubic_matrix_size);

#endif /* POWER_METHOD_H */
