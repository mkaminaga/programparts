#include <stdio.h>
#include "standard_error.h"

/* differential(double (*), double, double)
 * calculate the differential of one-variable function.
 * arg1: one-variable function
 * arg2: delta h
 * arg3: x cordinate of point to take differential */
double differential(double (*math_func) (double), double h, double x){
    double value = 0;

    value = (math_func(x + h) - math_func(x))/h;

   return value;
}
