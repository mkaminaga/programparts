#include <stdio.h>
#include <stdint.h>
#include "queue.h"

/* void init_queue(queue_t*)
 * initialize queue.
 * arg1: pointer to the queue */
void init_queue(queue_t* q) {
    uint32_t i = 0;

    for (i = 0; i < QUE_MAX; i++) q->box[i] = 0;

    q->head = 0;
    q->tail = 0;
}

/* void insert(queue_t*, uint32_t)
 * insert new element to the queue
 * arg1: pointer to the queue */
void insert(queue_t* q, uint32_t data) {

    if (q->tail >= QUE_MAX) return;

    q->box[q->tail] = data;
    q->tail++;
}

/* void delete(queue_t*)
 * delete old element of the que
 * arg1: pointer to the queue */
void take_out(queue_t* q) {

    if (q->head >= QUE_MAX) return;

    q->head++;
}

/* uint32_t queue_is_empty(queue_t*)
 * return true if queue_is_empty.
 * arg1: pointer to the queue */
uint32_t queue_is_empty(queue_t* q) {
    return (q->tail < q->head);
}

/* uint32_t get_top_of_queue(queue_t*)
 * return the oldest element of the queue.
 * arg1: pointer to the queue */
uint32_t get_top_of_queue(queue_t* q) {
    return q->box[q->head];
}

/* void show_inside_of_queue(queue_t*)
 * show inside of the queue for debug purpose.
 * arg1: pointer to the queue */
void show_inside_of_queue(queue_t* q) {
    uint32_t i = 0;

    if (queue_is_empty(q)) return;

    for (i = (uint32_t) q->head; i < (uint32_t) q->tail; i++) {
        printf("%u:%u ", i, q->box[i]);
    }
    printf("\n");
}
