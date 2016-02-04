#include <stdio.h>
#include <stdint.h>
#include "stack2d.h"

/* stack[n][0]:node num */
/* stack[n][1]:cost of path */

/* push to 2d stack. stack size can be changed by STACK_2D_DEAPTH */
void push_2d_stack(uint32_t node[2], uint32_t stack[][2]) {
    int32_t i = 0;

    for (i = STACK_2D_DEAPTH - 2; i >= 0; i--) {
        stack[i + 1][0] = stack[i][1]; //shift forward
        stack[i + 1][1] = stack[i][1];
    }
    stack[0][0] = node[0];
    stack[0][1] = node[1];
}

/* pop from 2d stack. stack size can be changed by STACK_2D_DEAPTH */
void pop_2d_stack(uint32_t stack[][2], uint32_t result[2]) {
    uint32_t i = 0;
    uint32_t temp = 0;

    temp = stack[0];
    for (i = 0; i < STACK_2D_DEAPTH - 1; i++) {
        stack[i][0] = stack[i + 1][0]; //shift backward
        stack[i][1] = stack[i + 1][1];
        stack[i + 1][0] = 0; //push 0 to tail
        stack[i + 1][1] = 0;
    }
    result[0] = stack[0][0]; //put result
    result[1] = stack[0][1];
}

/* fill the 2d stack with specific value */
void init_2d_stack(uint32_t value[2], uint32_t stack[][2]) {
    uint32_t i = 0;

    for (i = 0; i < STACK_2D_DEAPTH; i++) {
        stack[i][0] = value[0];
        stack[i][1] = value[1];
    }
}

/* show the existence of specific value in the 2d stack in designated depth */
uint8_t exist_2d_stack(uint32_t value, uint32_t stack[][2], uint32_t depth) {
    uint32_t i = 0;

    for (i = 0; i < depth; i++) {
        if (stack[i][0] == value) {
            return 1;
        }
    }
    return 0;
}

/* sort 2d stact in depth according to the key */
void sort_2d_stack(
    uint32_t stack[][2], uint8_t key, uint8_t way, uint32_t depth) {

}
