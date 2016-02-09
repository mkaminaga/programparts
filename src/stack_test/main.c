/* Date:2015/02/02 */
/* test stack. */

#include <stdio.h>
#include <stdint.h>
#include "../../lib/stack.h"

#define STACK_MAX 255
stack_t stack;

int main(int argc, char const* argv[]) {
    uint32_t i = 0;

    /* init stack */
    init_stack(&stack);

    /* push stack */
    for (i = 0; i < 'G' - 'A'; i++) {
        push(&stack, i + 'A');
        show_inside_stack(&stack);
    }

    /* pop stack */
    for (i = 0; i < 'G' - 'A'; i++) {
        pop(&stack);
        show_inside_stack(&stack);
    }
}

