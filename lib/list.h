#ifndef LIST_H
#define LIST_H

typedef struct element {
    uint32_t data;
    struct element* next;
} element_t;

/* element_t* init_list(element_t*)
 * initialize list with given element head.
 * return: memory allocation result
 * arg1: the pointer to be new head of the list */
element_t* init_list(element_t* e);

/* element_t* insert_to_list(element_t*, uint32_t, uint32_t)
 * insert new element to the list.
 * return: memory allocation result
 * arg1: the pointer to the head of the list
 * arg2: index of the element to be inserted */
element_t* insert_to_list(element_t* e, uint32_t k, uint32_t data);

/* uint32_t add_to_list(element_t*, uint32_t)
 * add new element to the list
 * return: memory allocation result
 * arg1: the pointer to the head of the list
 * arg2: data to be added */
element_t* add_to_list(element_t* e, uint32_t data);

/* void delete_from_list(element_t*, uint32_t)
 * arg1: the pointer to the head of the list
 * arg2: index of the element to be deleted */
void delete_from_list(element_t* e, uint32_t k);

/* void free_list(element_t*)
 * free heap memory allocated by all elements in the list
 * arg1: the pointer to the head of the list*/
void free_list(element_t* e);

/* void show_inside_of_list(element_t*)
 * show inside of the list for debug purpose.
 * arg1: the pointer to the head of the list*/
void show_inside_of_list(element_t* e);

#endif /* LIST_H */
