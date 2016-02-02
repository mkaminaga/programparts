#include <stdio.h>
#include <stdint.h>
#include "stack.h"

/* push to stack. stack size can be changed by STACK_DEAPTH */
void push(uint32_t node, uint32_t* stack) {
    int32_t i = 0;

    for (i = STACK_DEAPTH - 2; i >= 0; i--) {
        stack[i + 1] = stack[i];
    }
    stack[0] = node;
}

/* pop from stack. stack size can be changed by STACK_DEAPTH */
uint32_t pop(uint32_t* stack) {
    uint32_t i = 0;
    uint32_t temp = 0;

    temp = stack[0];
    for (i = 0; i < STACK_DEAPTH - 1; i++) {
        stack[i] = stack[i + 1];
    }
    return temp;
}
