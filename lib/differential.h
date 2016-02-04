#ifndef DIFFERENTIAL_H
#define DIFFERENTIAL_H

/* differential(double (*), double, double)
 * calculate the differential of one-variable function.
 * arg1: one-variable function
 * arg2: delta h
 * arg3: x cordinate of point to take differential */
double differential(double (*math_func) (double), double h, double x);

#endif /* DIFFERENTIAL_H */
