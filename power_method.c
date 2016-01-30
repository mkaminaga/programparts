#include <stdio.h>
#include <math.h>
#define OBJECT_NUM  3
#define EPSILON     1E-6

double lf_abs(double x);
double get_rayliegh_quatient(double* a, double* x, int row);
void set_matrix(double* a, double* x, int row, int column, double* y);
double get_dot(double* x, double* y, int row);

int main(int argc, char* argv[]){
    double a[OBJECT_NUM][OBJECT_NUM]={
            { 4, -4,  0},
            {-4,  8, -4},
            { 0, -4,  4}};
    double a_1d[OBJECT_NUM * OBJECT_NUM];
    double x[OBJECT_NUM] = {0.2, 0.3, 0.6};
    double x_new[OBJECT_NUM];
    
    int i = 0;
    int j = 0;
    double r = 0;
    double r_new = 0;

    /* 2d matrix -> 1d matrix */
    for(i = 0; i < OBJECT_NUM ; i++){
        for(j = 0; j < OBJECT_NUM ; j++){
            a_1d[i * OBJECT_NUM + j] = a[i][j];
        }
    }

    /* initial data */
    set_matrix(a_1d, x, OBJECT_NUM, OBJECT_NUM, x_new);
    r_new = get_rayliegh_quatient(a_1d, x_new, OBJECT_NUM);
    r = 0.0;

    while(lf_abs(r - r_new) > EPSILON){
        /* show progress */
        printf("rayleigh quatient = %10.6lf\n", r_new);  
        
        /* shift data */
        r = r_new;
        for(i = 0; i < OBJECT_NUM; i++){
            x[i] = x_new[i];
        }

        /* set new data */
        set_matrix(a_1d, x, OBJECT_NUM, OBJECT_NUM, x_new);
        r_new = get_rayliegh_quatient(a_1d, x_new, OBJECT_NUM);
    }

    /* show final result */
    printf("final rayleigh quatient = %10.5lf\n", r);  

    return 0;
}

double lf_abs(double x){
    if(x > 0){
        return x;
    }else{
        return -x;
    }
}

double get_rayliegh_quatient(double* a, double* x, int row){
    double value = 0;
    double y[row];

    set_matrix(a, x, row, row, y);
    value = get_dot(y, x, row) / get_dot(x, x, row);

    return value;
}

void set_matrix(double* a, double* x, int row, int column, double* y){
    int i = 0;
    int j = 0; 

    /* y = Ax */
    for(i = 0; i < row; i++){
        y[i] = 0.0;
        for(j = 0; j < column; j++){
            y[i] += a[i * column + j] * x[j];
        }
    }
}

double get_dot(double* x, double* y, int row){
    int i = 0;
    double value = 0;
    
    for(i = 0; i < row; i++){
        value += x[i] * y[i];    
    }

    return value;
}

