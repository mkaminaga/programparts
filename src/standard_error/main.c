#include <stdio.h>
#include "../../lib/standard_error.h"

#define ELEMENT_NUM 33

int main(){
    double measured[ELEMENT_NUM] = {
        160, 161, 155, 158, 157, 163, 163, 168, 153, 160,
        168, 151, 152, 160, 155, 164, 161, 166, 156, 164,
        157, 160, 155, 155, 167, 162, 159, 160, 158, 158,
        165, 157, 160
    };

    printf("average:    %lf\n", calc_average(measured, ELEMENT_NUM));
    printf("dispersion: %lf\n", calc_dispersion(measured, ELEMENT_NUM));
    printf("std err:    %lf\n", calc_standard_error(measured, ELEMENT_NUM));
    return 0;
}
