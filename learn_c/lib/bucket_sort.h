#ifndef BUCKET_SORT_H
#define BUCKET_SORT_H

/* type of data array */
typedef uint32_t data_t;

/* void bucket_sort(data_t[], data_t max, uint32_t)
 * sort array by bucket sort.
 * arg1: pointer to the data array
 * arg2: largest element in data array
 * arg3: length of data */
void bucket_sort(data_t a[], data_t max, uint32_t length);

#endif /* BUCKET_SORT_H */
