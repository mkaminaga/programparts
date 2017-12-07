#ifndef STANDARD_ERROR_H
#define STANDARD_ERROR_H

/* calc_standard_error(double[], uint32_t)
 * calculate standard error of data.
 * arg1: data
 * arg2: number of elemet in data */
double calc_standard_error(double data[], uint32_t element_num);

/* calc_dispersion(double[], uint32_t)
 * calcuate dispersion of data.
 * arg1: data
 * arg2: number of elemet in data */
double calc_dispersion(double data[], uint32_t element_num);

/* calc_average(double[], uint32_t)
 * calcuate average of data.
 * arg1: data
 * arg2: number of elemet in data */
double calc_average(double data[], uint32_t element_num);

#endif /* STANDARD_ERROR_H */
