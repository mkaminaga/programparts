#ifndef HEAP_H
#define HEAP_H

#ifndef HEAP_MAX
# define HEAP_MAX 255
#endif

/* type of data array */
typedef uint32_t data_t;

typedef struct {
    data_t box[HEAP_MAX];
    uint32_t size;
} heap_t;

/* void init_heap(heap_t*)
 * init the heap.
 * arg1: the pointer of heap */
void init_heap(heap_t* h);

/* void insert_to_heap(heap_t*, data_t)
 * insert data to the heap.
 * arg1: the pointer to the heap
 * arg2: data to be added */
void insert_to_heap(heap_t* h, data_t data);

/*uint32_t get_min_of_heap(heap_t*)
 * get minimum member of the heap.
 * agr1: the pointer to the heap */
data_t get_min_of_heap(heap_t* h);

/* void delete_min_of_heap(heap_t*)
 * delete minimum member of the heap.
 * arg1: the pointer to the heap */
void delete_min_of_heap(heap_t* h);

/* void show_inside_heap(heap_t*)
 * show inside of heap for debug purpose.
 * arg1: the pointer to the heap */
void show_inside_heap(heap_t* h);

/* void swap(data_t*, data_t*)
 * swap the two vwlues in designated address.
 * arg1: value1
 * arg2: value */
void swap(data_t*, data_t*);

#endif /* HEAP_H */
