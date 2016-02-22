#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "list.h"

/* element_t* new()
 * allocate new element_t object in heep memory.
 * return: memory allocation result */
element_t* new();

/* element_t* init_list(element_t*)
 * initialize list with given element head.
 * return: memory allocation result
 * arg1: the pointer to be new head of the list */
element_t* init_list(element_t* e) {
    if ((e = new()) != NULL)
        e->data = 0; //dammy data
    return e;
}

/* element_t* insert_to_list(element_t*, uint32_t, uint32_t)
 * insert new element to the list.
 * return: memory allocation result
 * arg1: the pointer to the head of the list
 * arg2: index of the element to be inserted */
element_t* insert_to_list(element_t* e, uint32_t k, uint32_t data) {

    /* trail to the index */
    while (k > 1 && e != NULL) {
        e = e->next; //shift index forward
        k--;
    }

    if (k > 1)
        return NULL; //index size error

    /* replace the element */
    if ((e = new()) == NULL) {
        return e;
    } else {
        e->data = data;
        e->next = e->next;
        e->next = e;
    }

    return e;
}

/* uint32_t add_to_list(element_t*, uint32_t)
 * add new element to the list
 * return: memory allocation result
 * arg1: the pointer to the head of the list
 * arg2: data to be added */
element_t* add_to_list(element_t* e, uint32_t data) {
    element_t* new_e = NULL;

    /* create new instance to be added */
    /* if ((new_e = new()) == NULL) */
    /*     return new_e; */
    /* else new_e->data = data; //set data */

    /* go to the end of the list */
    printf("e:%p\n", e);
    while (e->next != NULL)
        e = e->next;

    /* add new instance to the list */
    /* e->next = new_e; */

    return new_e;
}

/* void delete_from_list(element_t*, uint32_t)
 * arg1: the pointer to the head of the list
 * arg2: index of the element to be deleted */
void delete_from_list(element_t* e, uint32_t k) {
    element_t* temp;

    /* trail to the index */
    while (k > 1 && e != NULL) {
        e = e->next; //shift index forward
        k--;
    }

    if (k > 1)
        return; //index size error

    temp = e; //save pointer to be releaced
    e->next = e->next->next;
    free(temp);
}

/* void free_list(element_t*)
 * free heap memory allocated by all elements in the list
 * arg1: the pointer to the head of the list*/
void free_list(element_t* e) {
    element_t* temp;

    /* trail to the index */
    while (e != NULL) {
        temp = e->next; //save pointer to be released
        free(e);

#if defined(DEBUG)
    printf("freed:%p\n", e);
#endif

        e = temp; //shift index backward
    }
}

/* void show_inside_of_list(element_t*)
 * show inside of the list for debug purpose.
 * arg1: the pointer to the head of the list*/
void show_inside_of_list(element_t* e) {
    uint32_t i = 0;

    /* trail to the index */
    for (i = 0; e != NULL; i++, e = e->next)
        printf("%u:%u ", i, e->data);
    printf("\n");
}

/* element_t* new()
 * allocate new element_t object in heep memory.
 * return: pointer to the instance*/
element_t* new() {
    element_t* q;

    q = (element_t*) malloc(sizeof(element_t));
    q->next = NULL;

#if defined(DEBUG)
    printf("allocated:%p\n", q);
#endif

    return q;
}
