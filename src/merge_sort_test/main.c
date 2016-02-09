/* 2016/02/09
 *
 * How to sort 0 to 9 using merge sort?
 *
 *                2614059783
 *              /            \
 *         26140              59783
 *        /     \            /     \
 *      261      40       597      83
 *     /   \    /  \     /   \    /  \
 *    26    1  4    0   59    7  8    3
 *   /  \              /  \
 *  2    6            5    9
 *
 **/
#include <stdio.h>
#include <stdint.h>
#include "../../lib/merge_sort.h"

#define ARRAY_MAX 10

int main(int argc, char const* argv[]) {

    uint32_t a[ARRAY_MAX] = {
        2, 6, 1, 4, 0, 5, 9, 7, 8, 3,
    };
    uint32_t i = 0;

    /* show conditions */
    printf("before:");
    for (i = 0; i < ARRAY_MAX; i++) printf("%u:%u ", i, a[i]);
    printf("\n");

    /* process data */
    merge_sort(a, ARRAY_MAX);

    /* show result */
    printf("after :");
    for (i = 0; i < ARRAY_MAX; i++) printf("%u:%u ", i, a[i]);
    printf("\n");
}
