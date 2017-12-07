#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "bucket_sort.h"

/* void bucket_sort(data_t[], data_t max, uint32_t)
 * sort array by bucket sort.
 * arg1: pointer to the data array
 * arg2: largest element in data array
 * arg3: length of data */
void bucket_sort(data_t a[], data_t max, uint32_t length) {
    data_t* b;
    data_t none = max + 1;
    uint32_t i = 0;
    uint32_t j = 0;

    /* allocate tempolary memory */
    b = (data_t*) malloc((max + 1) * sizeof(data_t));

    /* set "blank" data */
    for (i = 0; i < max; i++)
        b[i] = none;

    /* bucket sort */
    for (i = 0; i < length; i++)
        b[a[i]] = a[i];

    /* set result */
    j = 0;
    for (i = 0; i < max; i++) {
        if (b[i] != none) {
            a[j] = b[i];
            j++;
        }
    }

    /* free heep memory */
    free(b);
}
