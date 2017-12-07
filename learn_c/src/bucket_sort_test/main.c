#include <stdio.h>
#include <stdint.h>
#include "../../lib/bucket_sort.h"

#define ARRAY_MAX 10

int main(int argc, char* argv[]) {

    data_t data[ARRAY_MAX] = {
        0, 8, 1, 3, 5, 4, 9, 7, 2, 6
    };

    /* show before */
    printf("before:%u ,%u ,%u ,%u ,%u ,%u ,%u ,%u ,%u ,%u\n",
        data[0], data[1], data[2], data[3], data[4],
        data[5], data[6], data[7], data[8], data[9]);

    /* sort */
    bucket_sort(data, 9, ARRAY_MAX); //9 is largest element.

    /* show after */
    printf("after: %u ,%u ,%u ,%u ,%u ,%u ,%u ,%u ,%u ,%u\n",
        data[0], data[1], data[2], data[3], data[4],
        data[5], data[6], data[7], data[8], data[9]);
    printf("\n");
}
