#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "../../lib/random.h"

#define ELEMENT_NUM 30

int main(int argc, char* argv[]){
    uint32_t data[ELEMENT_NUM];
    uint32_t i = 0;

    printf("%d\n", RAND_MAX);

    generate_random(data, ELEMENT_NUM, 0, 10);

    /* show result */
    for(i = 0; i < ELEMENT_NUM; i++) printf("data[%d] = %d\n", i, data[i]);

   return 0;
}
