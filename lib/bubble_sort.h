#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

/* sort given data.
 * arg1: given data
 * arg2: ascending(=1) and decending(=0)
 * arg3: depth of index to be sorted */
void bubble_sort(uint32_t data[], uint8_t way, uint32_t depth);

/* sort given data.
 * arg1: given data
 * arg2: key of sorting
 * arg2: ascending(=1) and decending(=0)
 * arg3: depth of index to be sorted */
void bubble_sort_2d(uint32_t data[][2], uint8_t key, uint8_t way, uint32_t depth);

#endif /* BUBBLE_SORT_H */
