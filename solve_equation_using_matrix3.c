#include <stdio.h>
#include <math.h>
#define ROW 4

void solve_equation(double a_p[ROW][ROW], double b_p[ROW], double x_p[ROW]);
void pivotting(double a[ROW][ROW], double b[ROW], int key);

int main(int argc, char* argv[]){
    double x[ROW];
    double a[ROW][ROW] = {
        {2.0, 4.0, -4.0, 8.0},
        {5.0, 8.0, 4.0, -2.0},
        {-3.0, -6.0, 2.0, 1.0},
        {6.0, 7.0, -1.0, 3.0}
    };
    double b[ROW] = {2.0, -1.0, 13.0, -1.0};
    
    /* 
    double a[ROW][ROW] = {
        {2.0, 4.0, -4.0, 8.0},
        {-3.0, -6.0, 2.0, 1.0},
        {5.0, 8.0, 4.0, -2.0},
        {6.0, 7.0, -1.0, 3.0}
    };
    double b[ROW] = {2.0,13.0, -1.0, -1.0};
    */
    
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
        /* pivotting */
        //pivotting(a, b, i);

        for(j = i + 1; j < ROW; j++){
            /* pivot */
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

void pivotting(double a[ROW][ROW], double b[ROW], int key){
    int i = 0;
    int j = 0;
    int temp = 0;
    int flag = 1;

   /* bubble sort_by_key */ 
    while(flag == 1){ 
        flag = 0;
        for(i = 0; i < ROW - 1; i++){
            if(a[i+1][key] > a[i][key]){
                /* about b */
                temp = b[i+1];
                b[i+1] = b[i];
                b[i] = temp;
                
                /* about a */
                for(j = 0; j < ROW; j++){
                    /* about a */
                    temp = a[i+1][j];
                    a[i+1][j] = a[i][j];
                    a[i][j] = temp;      
                }
                flag = 1;
            }
        }
    }
}


