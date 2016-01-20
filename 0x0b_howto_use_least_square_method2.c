#include <stdio.h>
#include <math.h>

#define PLOT_NUM 10
#define ORDER 3 //if x^3, set 4
#define ROW ORDER + 1

void get_least_square(double x[PLOT_NUM], double y[PLOT_NUM], double a[PLOT_NUM]);
double get_sum(double x[], int n);
double get_crossed_sum(double x[], double y[], int n);
void solve_equation(double a_p[ROW][ROW], double b_p[ROW], double x_p[ROW]);

int main(int argc, char* argv[]){
    int i = 0;
    double x[PLOT_NUM]
        = {1.0 , 2.0 , 3.0 , 4.0 ,  5.0,  6.0,  7.0,  8.0,  9.0, 10.0};
    double y[PLOT_NUM]
        = {24.5, 20.7, 18.1, 16.4, 15.0, 14.2, 13.6, 13.0, 12.4, 12.1};
    double a[PLOT_NUM];

    /* calculate */
    get_least_square(x, y, a);

    /* show result */
    for(i = 0; i <= ORDER; i++){
        printf("a[%d] = %10.5lf\n", i, a[i]);
    }
    return 0;
}

void get_least_square(
        double x[PLOT_NUM], double y[PLOT_NUM], double a[PLOT_NUM]){
    double c[ROW][ROW];
    double d[ROW];
    double val[PLOT_NUM];
    int k = 0;
    int i = 0;
    int j = 0;

    for(k = 0; k <= ORDER; k++){
        /* set matrix c */
        for(j = 0; j <= ORDER; j++){
            for(i = 0; i < PLOT_NUM; i++){
                val[i] = pow(x[i], k + j);
            }
            c[k][j] = get_sum(val, PLOT_NUM);
        }

        /* set vector d */
        for(i = 0; i < PLOT_NUM; i++){
            val[i] = pow(x[i], k);
        }
        d[k] = get_crossed_sum(y, val, PLOT_NUM);
    }

   /* get result */
    solve_equation(c, d, a);
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

void solve_equation(double a_p[ROW][ROW], double b_p[ROW], double x_p[ROW]){
    double a[ROW][ROW];
    double b[ROW];

    int i = 0;
    int j = 0;
    int k = 0;
    double p = 0;

    /* copy argument values for protection */
    for(i = 0; i < ROW; i++){
        for(j = 0; j < ROW; j++){
            a[i][j] = a_p[i][j];
        }
    }

    for(i = 0; i < ROW; i++){
        b[i] = b_p[i];
    }

    /* zennshin shoukyo */
    for(i = 0; i < ROW - 1; i++){
        for(j = i + 1; j < ROW; j++){
            /* pibot */
            p = a[j][i] / a[i][i];

            /* eliminate LS */
            for(k = i; k < ROW; k++){
                a[j][k] = a[j][k] - p * a[i][k];
            }

            /* eliminate RS */
            b[j] = b[j] - p * b[i];
        }
    }

    /* koutai dainyuu */
    for(i = ROW - 1; i >= 0; i--){
        x_p[i] = b[i] / a[i][i];

        for(j = i + 1; j < ROW; j++){
            x_p[i] = x_p[i] - (a[i][j] / a[i][i]) * x_p[j];
        }
    }
}

