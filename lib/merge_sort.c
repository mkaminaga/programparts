#include <stdio.h>
#include <stdint.h>
#include "merge_sort.h"

/* void merge(uint32_t[], uint32_t, uint32_t)
 * merge designate array segment
 * arg1: pointer of the array
 * arg2: start index of the segmet to be merged
 * arg3: length of the segment to e merged */
void merge(uint32_t a[], uint32_t start, uint32_t len);

/* void msort(uint32_t[], uint32_t, uint32_t)
 * divide and merge recrusivly.
 * arg1: pointer to the array
 * arg2: index of segment head
 * arg3: length of segmant */
void msort(uint32_t a[], uint32_t start, uint32_t length);

/* void merge_sort(uint32_t[], uint32_t)
 * sort elements of array using merge sort.
 * arg1: pointer of the array
 * arg2: length of array */
void merge_sort(uint32_t a[], uint32_t length) {
    msort(a, 0, length);
}

/* void msort(uint32_t[], uint32_t, uint32_t)
 * divide and merge recrusivly.
 * arg1: pointer to the array
 * arg2: index of segment head
 * arg3: length of segmant */
void msort(uint32_t a[], uint32_t start, uint32_t length) {
    uint32_t mid = 0;

    if (length > 1) {
        mid = length / 2;
        msort(a, start, mid);
        msort(a, start + mid, length - mid);
        merge(a, start, length);
    }
}

/* void merge(uint32_t[], uint32_t, uint32_t)
 * merge designate array segment
 * arg1: pointer of the array
 * arg2: start index of the segmet to be merged
 * arg3: length of the segment to e merged */
void merge(uint32_t a[], uint32_t start, uint32_t len) {
    uint32_t b[len]; //temporaly array
    uint32_t ptr1 = 0; //index: left leaf of segment
    uint32_t ptr2 = 0; //index: right leaf of segment
    uint32_t mid = 0; //middle of segment
    uint32_t i = 0;

    mid = len / 2;
    ptr1 = start;
    ptr2 = start + mid;

    /* merge */
    for (i = 0; i < len; i++) {
        /* compere, then insert smaller data */
        if (ptr2 == start + len || (ptr1 < start + mid && a[ptr1] <= a[ptr2])) {
            b[i] = a[ptr1];
            ptr1++;
        } else {
            b[i] = a[ptr2];
            ptr2++;
        }
    }

    /* copy */
    for (i = 0; i < len; i++) a[start + i] = b[i];
}
