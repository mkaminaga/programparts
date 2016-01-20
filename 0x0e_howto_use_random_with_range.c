#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_MAX 100

int main(int argc, char* argv[]){
    int array_floor = 0;
    int array_cieal = 10;
    int array[ARRAY_MAX];
    int i = 0;

    printf("%d\n", RAND_MAX);

    /* set seed */
    srand((unsigned int) time(NULL));

    /* get random num */
    for(i = 0; i < ARRAY_MAX; i++){
       int temp = rand();
       array[i] = array_floor
           + (int) (temp * (array_cieal - array_floor + 1.0)
                   / (RAND_MAX + 1.0));
    }

    /* show result */
    for(i = 0; i < ARRAY_MAX; i++){
        printf("array[%d] = %d\n", i, array[i]);
    }

   return 0;
}
