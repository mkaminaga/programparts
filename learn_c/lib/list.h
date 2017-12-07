#ifndef LIST_H
#define LIST_H

/* type of data array */
typedef uint32_t data_t;

typedef struct element {
    data_t data;
    struct element* next;
} element_t;

/* void init_list(element_t**)
 * initialize list with given element head.
 * arg1: the pointer to be new head pointer of the list */
void init_list(element_t** e_pp);

/* void insert_to_list(element_t*, uint32_t, data_t)
 * insert new element to the list.
 * arg1: the pointer to the head of the list
 * arg2: index of the element to be inserted */
void insert_to_list(element_t* e, uint32_t k, data_t data);

/* void add_to_list(element_t*, data_t)
 * add new element to the list
 * arg1: the pointer to the head of the list
 * arg2: data to be added */
void add_to_list(element_t* e, data_t data);

/* void delete_from_list(element_t*, data_t)
 * arg1: the pointer to the head of the list
 * arg2: index of the element to be deleted */
void delete_from_list(element_t* e, data_t k);

/* void free_list(element_t*)
 * free heap memory allocated by all elements in the list
 * arg1: the pointer to the head of the list*/
void free_list(element_t* e);

/* void show_inside_of_list(element_t*)
 * show inside of the list for debug purpose.
 * arg1: the pointer to the head of the list*/
void show_inside_of_list(element_t* e);

#endif /* LIST_H */
