#include <stdio.h>
#include <math.h>
#define DATA_SIZE 6

void get_least_square(double x[], double y[], int n, double a[2]);
double get_sum(double x[], int n);
double get_crossed_sum(double x[], double y[], int n);

int main(int argc, char* argv[]){
    int i = 0;
    double x[] = {0.0 , 1.0 , 2.0 , 3.0 , 4.0 , 5.0};
    double y[] = {10.2, 12.0, 15.7, 17.0, 20.5, 22.4};
    double a[2];

    /* calculate */
    get_least_square(x, y, DATA_SIZE, a);

    /* show resule */
    printf("a: %10.5lf\n", a[0]);
    printf("b: %10.5lf\n", a[1]);
    return 0;
}

void get_least_square(double x[], double y[], int n, double a[2]){
    double sum_x2 = get_crossed_sum(x, x, n);
    double sum_xy = get_crossed_sum(x, y, n);
    double sum_x = get_sum(x, n);
    double sum_y = get_sum(y, n);

    a[0] = (n * sum_xy - sum_x * sum_y)/(n * sum_x2 - pow(sum_x, 2));
    a[1] = (sum_x2 * sum_y - sum_x * sum_xy)/(n * sum_x2 - pow(sum_x, 2));
}

double get_sum(double x[], int n){
    int i = 0;
    double value = 0;

    for(i = 0; i < n; i++){
        value += x[i];
    }
    return value;
}

double get_crossed_sum(double x[], double y[], int n){
    int i = 0;
    double value = 0;

    for(i = 0; i < n; i++){
        value += x[i] * y[i];
    }
    return value;
}

