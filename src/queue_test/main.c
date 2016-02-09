/* Date:2015/02/02 */
/* test queue. */

#include <stdio.h>
#include <stdint.h>
#include "../../lib/queue.h"

queue_t queue;

int main(int argc, char const* argv[]) {
    uint32_t i = 0;
    uint32_t j = 0;

    /* initialize queue */
    init_queue(&queue);

    /* insert elements to the queue */
    printf("insert\n");
    for (i = 0; i < 'G' - 'A'; i++) {
        insert(&queue, i + 'A');
        show_inside_of_queue(&queue);
    }
    printf("\n");

    /* take out form queue */
    printf("take out\n");
    for (i = 0; i < 'G' - 'A'; i++) {
        take_out(&queue);
        show_inside_of_queue(&queue);
    }
    printf("\n");

    /* ling buffer */
    printf("ling buffer\n");
    for (i = 0; i < 3; i++) {
        printf("i = %u\n", i);
        for (j = 0; j < 'G' - 'A'; j++) {
            insert(&queue, j + 'A');
        }
        show_inside_of_queue(&queue);
        for (j = 0; j < 'F' - 'A'; j++) {
            take_out(&queue);
        }
        show_inside_of_queue(&queue);
        printf("\n");
    }
}
