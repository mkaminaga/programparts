#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "standard_error.h"

/* calc_standard_error(double[], uint32_t)
 * calculate standard error of data.
 * arg1: data
 * arg2: number of elemet in data */
double calc_standard_error(double data[], uint32_t element_num){
    double value = sqrt(calc_dispersion(data, element_num));

    return value;
}

/* calc_dispersion(double[], uint32_t)
 * calcuate dispersion of data.
 * arg1: data
 * arg2: number of elemet in data */
double calc_dispersion(double data[], uint32_t element_num){
    double value = 0;
    int i = 0;
    double average = calc_average(data, element_num);

    for(i = 0; i < element_num; i++){
        value += (data[i] - average) * (data[i] - average);
    }
    value  =  value/element_num;
    return value;
}

/* calc_average(double[], uint32_t)
 * calcuate average of data.
 * arg1: data
 * arg2: number of elemet in data */
double calc_average(double data[], uint32_t element_num){
    double value = 0;
    int i = 0;

    for(i = 0; i < element_num; i++){
        value +=  data[i];
    }
    value = (double) value/element_num;
    return value;
}
