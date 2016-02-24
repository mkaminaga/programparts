#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "gauss_jordan_iteration.h"
#include "least_square.h"

double get_sum(double x[], uint32_t n);
double get_crossed_sum(double x[], double y[], uint32_t n);

/* least_square(uint32_t, uint32_t, double, double, double)
 * arg1: number od data points
 * arg2: order of approximate curve
 * arg3: x cordinates of plots
 * arg4: y cordinates of plots
 * arg5: solution */
void least_square(
        uint32_t plot_num, uint32_t order, double x[], double y[], double a[]){

    double c[(order + 1) * (order + 1)];
    double d[order + 1];
    double temp[plot_num];
    uint32_t i = 0;
    uint32_t j = 0;
    uint32_t k = 0;

    for(k = 0;  k <= order; k++){

        /* set matrix c */
        for(j = 0; j <= order; j++){
            for(i = 0; i < plot_num; i++) temp[i] = pow(x[i], k + j);
            c[k * (order + 1) + j] = get_sum(temp, plot_num);
        }

        /* set vector d */
        for(i = 0; i < plot_num; i++) temp[i] = pow(x[i], k);
        d[k] = get_crossed_sum(y, temp, plot_num);
    }

    /* get result */
    gauss_jordan_iteration(order + 1, c, d, a);
}

double get_sum(double x[], uint32_t n){
    uint32_t i = 0;
    double value = 0;

    for(i = 0; i < n; i++) value += x[i];

    return value;
}

double get_crossed_sum(double x[], double y[], uint32_t n){
    uint32_t i = 0;
    double value = 0;

    for(i = 0; i < n; i++) value += x[i] * y[i];

    return value;
}
