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
        e->next = NULL;
    return e;
}

/* element_t* insert_to_list(element_t*, uint32_t, uint32_t)
 * insert new element to the list.
 * return: memory allocation result
 * arg1: the pointer to the head of the list
 * arg2: index of the element to be inserted */
element_t* insert_to_list(element_t* e, uint32_t k, uint32_t data) {
    element_t* temp;

    /* trail to the index */
    while (k > 1 && e != NULL) {
        e = e->next; //shift index forward
        k--;
    }

    if (k > 1)
        return NULL; //index size error

    /* replace the element */
    if ((temp = new()) == NULL) {
        return temp;
    } else {
        temp->data = data;
        temp->next = e->next;
        e->next = temp;
    }

    return temp;
}

/* uint32_t add_to_list(element_t*, uint32_t)
 * add new element to the list
 * return: memory allocation result
 * arg1: the pointer to the head of the list
 * arg2: data to be added */
element_t* add_to_list(element_t* e, uint32_t data) {
    element_t* q;

    /* track to the end of the list */
    while (e != NULL)
        e = e->next; //shift index forward

    /* replace tail of the list */
    if ((q = new()) == NULL) {
        return q;
    } else {
        q->data = data;
        q->next = e->next;
        e->next = q;
    }

    return q;
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
        e = temp; //shift index backward
    }
    printf("free successful\n");
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
    return (element_t*) malloc(sizeof(element_t));
}
