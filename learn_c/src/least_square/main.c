#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "../../lib/least_square.h"

#define PLOT_NUM 10
#define ORDER 3 //if x^3, set 4

int main(int argc, char* argv[]){
    double x[PLOT_NUM] = {
        1.0 , 2.0 , 3.0 , 4.0 ,  5.0,  6.0,  7.0,  8.0,  9.0, 10.0
    };

    double y[PLOT_NUM] = {
        24.5, 20.7, 18.1, 16.4, 15.0, 14.2, 13.6, 13.0, 12.4, 12.1
    };

    double a[PLOT_NUM];
    uint32_t i = 0;

    /* calculate */
    least_square(PLOT_NUM, ORDER, x, y, a);

    /* show result */
    for(i = 0; i <= ORDER; i++) printf("a[%d] = %10.5lf\n", i, a[i]);

    return 0;
}
