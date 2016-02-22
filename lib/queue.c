#include <stdio.h>
#include <stdint.h>
#include "queue.h"

/* void init_queue(queue_t*)
 * initialize queue.
 * arg1: pointer to the queue */
void init_queue(queue_t* q) {
    uint32_t i = 0;

    for (i = 0; i < QUEUE_MAX; i++) q->box[i] = 0;

    q->head = 1;
    q->tail = 0;
    q->flag = 0;
}

/* void insert(queue_t*, data_t)
 * insert new element to the queue
 * arg1: pointer to the queue */
void insert(queue_t* q, data_t data) {

    q->tail++;

    /* manage ling buffer */
    if (q->tail == QUEUE_MAX) {
        q->tail = 1;
        if (q->flag == 0) q->flag = 1;
        else q->flag = 0;
    }

    q->box[q->tail] = data;
}

/* void delete(queue_t*)
 * delete old element of the que
 * arg1: pointer to the queue */
void take_out(queue_t* q) {

    q->head++;

    /* manage ling buffer */
    if (q->head == QUEUE_MAX) {
        q->head = 1;
        if (q->flag == 0) q->flag = 1;
        else q->flag = 0;
    }
}

/* data_t queue_is_empty(queue_t*)
 * return true if queue_is_empty or que overflow.
 * arg1: pointer to the queue */
data_t queue_is_empty(queue_t* q) {
    if (q->flag == 0) return (q->tail < q->head);
    return (q->tail >= q->head);
}

/* data_t get_top_of_queue(queue_t*)
 * return the oldest element of the queue.
 * arg1: pointer to the queue */
data_t get_top_of_queue(queue_t* q) {
    return q->box[q->head];
}

/* void show_inside_of_queue(queue_t*)
 * show inside of the queue for debug purpose.
 * arg1: pointer to the queue */
void show_inside_of_queue(queue_t* q) {
    uint32_t i = 0;

    if (q->flag == 0) {
        for (i = q->head; i <= q->tail; i++)
            printf("%u:%u ", i, q->box[i]);
    } else {
        for (i = q->head; i != q->tail + 1 && !queue_is_empty(q); i++){
            if (i == QUEUE_MAX) i = 1;
            printf("%u:%u ", i, q->box[i]);
        }
    }
    printf("\n");
}
