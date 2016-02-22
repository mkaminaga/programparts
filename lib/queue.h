#ifndef QUEUEH
#define QUEUEH

/* user stack size. default is 255 */
#ifndef QUEUE_MAX
# define QUEUE_MAX 255
#endif

typedef uint32_t data_t;

typedef struct {
    data_t box[QUEUE_MAX];
    uint32_t head;
    uint32_t tail;
    uint32_t flag : 1;
} queue_t;

/* void init_queue(queue_t*)
 * initialize queue.
 * arg1: pointer to the queue */
void init_queue(queue_t* q);

/* void insert(queue_t*, data_t)
 * insert new element to the queue
 * arg1: pointer to the queue */
void insert(queue_t* q, data_t data);

/* void delete(queue_t*)
 * delete old element of the que
 * arg1: pointer to the queue */
void take_out(queue_t* q);

/* data_t queue_is_empty(queue_t*)
 * return true if queue_is_empty or que overflow.
 * arg1: pointer to the queue */
data_t queue_is_empty(queue_t* q);

/* data_t get_top_of_queue(queue_t*)
 * return the oldest element of the queue.
 * arg1: pointer to the queue */
data_t get_top_of_queue(queue_t* q);

/* void show_inside_of_queue(queue_t*)
 * show inside of the queue for debug purpose.
 * arg1: pointer to the queue */
void show_inside_of_queue(queue_t* q);

#endif /* QUEUEH */
