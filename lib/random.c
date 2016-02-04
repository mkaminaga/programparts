#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "random.h"

/* generate_random(uint32_t, uint32_t, uint32_t, uint32_t)
 * generate random in desgnated range
 * arg1: data
 * arg2: numbre of elements in data
 * arg3: minimun num to be generated
 * arg4: maximum num to be generated */
void generate_random(
        uint32_t data[], uint32_t element_num, uint32_t floor, uint32_t cieal) {

    uint32_t i = 0;

    /* set seed */
    srand((uint32_t) time(NULL));

    /* get random num */
    for(i = 0; i < element_num; i++){
       uint32_t temp = rand();
       data[i] = floor
           + (uint32_t) (temp * (cieal - floor + 1.0) / (RAND_MAX + 1.0));
    }
}
