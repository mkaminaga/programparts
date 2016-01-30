#include <stdio.h>
#include <math.h>
#define LENGTH 33

double calc_stderr(double* array);
double calc_dispersion(double* array);
double calc_average(double* array);

int main(){
    double measured[LENGTH] = {
        160, 161, 155, 158, 157, 163, 163, 168, 153, 160,
        168, 151, 152, 160, 155, 164, 161, 166, 156, 164,
        157, 160, 155, 155, 167, 162, 159, 160, 158, 158,
        165, 157, 160
    };

    printf("average:    %f\n", calc_average(measured));
    printf("dispersion: %f\n", calc_dispersion(measured));
    printf("std err:    %f\n", calc_stderr(measured));
    return 0;
}

double calc_stderr(double* array){
    double value=sqrt(calc_dispersion(array));

    return value;
}

double calc_dispersion(double* array){
    double value=0;
    int i=0;
    double average = calc_average(array);

    for(i=0; i<LENGTH; i++){
        value += (array[i] - average) * (array[i] - average);
    }
    value = value/LENGTH;
    return value;
}

double calc_average(double* array){
    double value = 0;
    int i=0;

    for(i=0; i< LENGTH; i++){
        value += array[i];
    }
    value = (double) value/LENGTH;
    return value;
}
