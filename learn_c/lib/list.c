#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "list.h"

/* element_t* new()
 * allocate new element_t object in heep memory.
 * return: memory allocation result */
element_t* new();

/* void init_list(element_t**)
 * initialize list with given element head.
 * arg1: the pointer to be new head pointer of the list */
void init_list(element_t** e_pp) {
    if ((*e_pp = new()) != NULL)
        (*e_pp)->data = 0; //dammy data
}

/* void insert_to_list(element_t*, uint32_t, data_t)
 * insert new element to the list.
 * arg1: the pointer to the head of the list
 * arg2: index of the element to be inserted */
void insert_to_list(element_t* e, uint32_t k, data_t data) {
    element_t* new_e = NULL;

    /* trail to the index */
    while (e != NULL && k > 1) {
        e = e->next; //shift index forward
        k--;
    }

    if (k > 1)
        return; //index size error

    /* replace the element */
    if ((new_e = new()) == NULL) {
        return;
    } else {
        new_e->data = data;
        new_e->next = e->next;
        e->next = new_e;
    }
}

/* void add_to_list(element_t*, data_t)
 * add new element to the list
 * arg1: the pointer to the head of the list
 * arg2: data to be added */
void add_to_list(element_t* e, data_t data) {
    element_t* new_e = NULL;

    /* create new instance to be added */
    if ((new_e = new()) == NULL)
        return;
    else new_e->data = data; //set data

    /* go to the end of the list */
    while (e->next != NULL)
        e = e->next;

    /* add new instance to the list */
    e->next = new_e;
}

/* void delete_from_list(element_t*, data_t)
 * arg1: the pointer to the head of the list
 * arg2: index of the element to be deleted */
void delete_from_list(element_t* e, data_t k) {
    element_t* temp;

    /* trail to the index */
    while (e != NULL && k > 1) {
        e = e->next; //shift index forward
        k--;
    }

    if (k > 1)
        return; //index size error

    temp = e->next; //save pointer to be releaced
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
