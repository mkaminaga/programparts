#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <math.h>
#include "merge_sort.h"
#include "stack.h"

/* void merge_sort(uint32_t[], uint32_t)
 * sort elements of array using merge sort.
 * arg1: array
 * arg2: length of array */
void merge_sort(uint32_t a[], uint32_t length) {

    stack_t stack;

    uint32_t node = 1;
    uint32_t flag = 0;
    uint32_t node_max = 0;
    int32_t i = 0;
    uint32_t j = 0;

    /* set depth */
    node_max = (uint32_t) log2(length) + 1;
    node_max = (uint32_t) pow(2, node_max);
    printf("%u\n", node_max);

    /* initialize stack */
    init_stack(&stack);

    /* push root node 1 */
    push(&stack, 1);

    while (!stack_is_empty(&stack)) {

        /* get current node */
        node = get_top_of_stack(&stack);
        pop(&stack);

        if (node < node_max) {
            for (i = 1; i >= 0; i--) {
                flag = 1;
                for (j = 0; j <= stack.top; j++) {
                    if (stack.box[j] == node * 2 + i) flag = 0;
                }
                if (flag == 1) push(&stack, node * 2 + i);
            }
        }

        /* debug line */
        printf("node:%u\n", node);
        usleep(2E5);
    }
}
