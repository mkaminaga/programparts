#include <stdio.h>
#include <stdint.h>
#include "heap.h"

/* void init_heap(heap_t*)
 * init the heap.
 * arg1: the pointer of heap */
void init_heap(heap_t* h) {
    h->size = 0;
}

/* void insert_to_heap(heap_t*, data_t)
 * insert data to the heap.
 * arg1: the pointer to the heap
 * arg2: data to be added */
void insert_to_heap(heap_t* h, data_t data) {
    uint32_t i = 0;

    /* set data to leaf */
    h->size++;
    h->box[h->size] = data;

    /* swap nodes according to heap rule */
    for (i = h->size; i > 1 && h->box[i] < h->box[i / 2]; i /= 2)
        swap(&h->box[i], &h->box[i / 2]);
}

/*data_t get_min_of_heap(heap_t*)
 * get minimum member of the heap.
 * agr1: the pointer to the heap */
data_t get_min_of_heap(heap_t* h) {
    return h->box[1];
}

/* void delete_min_of_heap(heap_t*)
 * delete minimum member of the heap.
 * arg1: the pointer to the heap */
void delete_min_of_heap(heap_t* h) {
    uint32_t i = 0;
    uint32_t k = 0;

    /* delete root node (min) of the heap */
    h->box[1] = h->box[h->size];
    h->size--;

    /* swap nodes according to heap rule */
    for (i = 1; i < h->size / 2; i = k) {
        k = 2 * i;
        if (k < h->size && h->box[k] > h->box[k + 1]) k++;
        if (h->box[i] <= h->box[k]) break;
        swap(&h->box[i], &h->box[k]);
    }
}

/* void show_inside_heap(heap_t*)
 * show inside of heap for debug purpose.
 * arg1: the pointer to the heap */
void show_inside_heap(heap_t* h) {
    uint32_t i = 0;

    for (i = 1; i <= h->size; i++) printf("%u:%u ", i, h->box[i]);
    printf("\n");
}

/* void swap(data_t*, data_t*)
 * swap the two vwlues in designated address.
 * arg1: value1
 * arg2: value */
void swap(data_t* ptr1, data_t* ptr2) {
    uint32_t temp = 0;

    temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}
