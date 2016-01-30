#include <stdio.h>
#define ROW 3

void solve_equation(double a_p[ROW][ROW], double b_p[ROW], double x_p[ROW]);

int main(int argc, char* argv[]){
    double a[ROW][ROW]
        = {{2.0, 2.0, 6.0}, {5.0, 7.0, 9.0}, {-3.0, 6.0, 4.0}};
    double b[ROW] = {14.0, 17.0, -2.0};
    double x[ROW];
    
    solve_equation(a, b, x);
   
   /* show results */ 
    int i = 0;
    int j = 0;

    /* matrix */
    printf("A\n");
    for(i = 0; i<ROW; i++){
        for(j = 0; j<ROW; j++){
            printf("%15.5f", a[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    /* RS */
    printf("b\n");
    for(i = 0; i<ROW; i++){
            printf("%15.5f", b[i]);
    }
    printf("\n");

    /* answer */
    printf("x\n");
    for(i = 0; i<ROW; i++){
            printf("%15.5f", x[i]);
    }
    printf("\n");

    return 0;
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
