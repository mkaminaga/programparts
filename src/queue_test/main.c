/* Date:2015/02/02 */
/* test queue. */

#include <stdio.h>
#include <stdint.h>
#include "../../lib/queue.h"

#define QUE_DEPTH 255
queue_t queue;

int main(int argc, char const* argv[]) {
    uint32_t i = 0;

    /* initialize queue */
    init_queue(&queue);

    /* insert elements to the queue */
    for (i = 0; i < 'G' - 'A'; i++) {
        insert(&queue, i + 'A');
        show_inside_of_queue(&queue);
    }

    /* take out form queue */
    for (i = 0; i < 'G' - 'A'; i++) {
        take_out(&queue);
        show_inside_of_queue(&queue);
    }
}
