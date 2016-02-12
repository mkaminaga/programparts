/* 2016/02/12
 * How to sort 0 to 9 using merge sort? */
#include <stdio.h>
#include <stdint.h>
#include "../../lib/quick_sort.h"

#define ARRAY_MAX 10

int main(int argc, char const* argv[]) {

    uint32_t a[ARRAY_MAX] = {
        2, 6, 1, 4, 0, 5, 9, 7, 8, 3,
    };
    uint32_t i = 0;

    /* show conditions */
    printf("before:");
    for (i = 0; i < ARRAY_MAX; i++) printf("%u ", a[i]);
    printf("\n");

    /* process data */
    quick_sort(a, ARRAY_MAX);

    /* show result */
    printf("after :");
    for (i = 0; i < ARRAY_MAX; i++) printf("%u ", a[i]);
    printf("\n");
}
