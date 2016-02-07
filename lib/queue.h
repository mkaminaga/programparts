#ifndef QUE_H
#define QUE_H

/* user stack size. default is 255 */
#ifndef QUE_DEPTH
# define QUE_DEPTH 255
#endif

typedef struct {
    uint32_t box[QUE_DEPTH];
    uint32_t head;
    uint32_t tail;
} queue_t;

/* void init_queue(queue_t*)
 * initialize queue.
 * arg1: pointer to the queue */
void init_queue(queue_t* q);

/* void insert(queue_t*, uint32_t)
 * insert new element to the queue
 * arg1: pointer to the queue */
void insert(queue_t* q, uint32_t data);

/* void delete(queue_t*)
 * delete old element of the que
 * arg1: pointer to the queue */
void take_out(queue_t* q);

/* uint32_t queue_is_empty(queue_t*)
 * return true if queue_is_empty.
 * arg1: pointer to the queue */
uint32_t queue_is_empty(queue_t* q);

/* uint32_t get_top_of_queue(queue_t*)
 * return the oldest element of the queue.
 * arg1: pointer to the queue */
uint32_t get_top_of_queue(queue_t* q);

/* void show_inside_of_queue(queue_t*)
 * show inside of the queue for debug purpose.
 * arg1: pointer to the queue */
void show_inside_of_queue(queue_t* q);

#endif /* QUE_H */
