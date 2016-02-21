#include <stdio.h>

#define ROW 3
#define COLUMN 5

int main(int argc, char** argv){
    int ninzu[ROW][COLUMN];
    int class_ninzu[ROW];
    int i = 0;
    int j = 0;

    /* clear buffer */
    for(i = 0; i< ROW; i++){
        class_ninzu[i] = 0;
    }

    /* list of popolation */
    ninzu[0][0] = 45;
    ninzu[0][1] = 46;
    ninzu[0][2] = 41;
    ninzu[0][3] = 39;
    ninzu[0][4] = 48;

    ninzu[1][0] = 45;
    ninzu[1][1] = 39;
    ninzu[1][2] = 52;
    ninzu[1][3] = 40;
    ninzu[1][4] = 45;

    ninzu[2][0] = 48;
    ninzu[2][1] = 46;
    ninzu[2][2] = 48;
    ninzu[2][3] = 48;
    ninzu[2][4] = 40;

    /* get sum */
    for(i = 0; i < ROW; i++){
        for(j = 0; j < COLUMN; j++){
            class_ninzu[i] += ninzu[i][j];
        }
    }

    /* output result */
    for(i = 0; i< ROW; i++){
        printf("class%d: %d\n", i, class_ninzu[i]);
    }

    return 0;
}
