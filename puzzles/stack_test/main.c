/* Date:2015/02/02 */
/* test my original stack. */

#include <stdio.h>
#include <stdint.h>
#include "../lib/stack.h"

#define STACK_DEAPTH 255
uint32_t stack[STACK_DEAPTH] = {0};

int main(int argc, char const* argv[]) {
    push('A', stack);
    printf("pushed A:%c\n", (char) stack[0]);
    push('B', stack);
    printf("pushed B:%c\n", (char) stack[0]);
    push('C', stack);
    printf("pushed C:%c\n", (char) stack[0]);
    push('D', stack);
    printf("pushed D:%c\n", (char) stack[0]);
    push('F', stack);
    printf("pushed F:%c\n", (char) stack[0]);

    printf("poped:%c\n", (char) pop(stack));
    printf("poped:%c\n", (char) pop(stack));
    printf("poped:%c\n", (char) pop(stack));
    printf("poped:%c\n", (char) pop(stack));
    printf("poped:%c\n", (char) pop(stack));
}
