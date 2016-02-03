#include <stdio.h>
#include <stdint.h>
#include "stack.h"

/* push to stack. stack size can be changed by STACK_DEAPTH */
void push(uint32_t node, uint32_t* stack) {
    int32_t i = 0;

    for (i = STACK_DEAPTH - 2; i >= 0; i--) {
        stack[i + 1] = stack[i]; //shift index
    }
    stack[0] = node;
}

/* pop from stack. stack size can be changed by STACK_DEAPTH */
uint32_t pop(uint32_t* stack) {
    uint32_t i = 0;
    uint32_t temp = 0;

    temp = stack[0];
    for (i = 0; i < STACK_DEAPTH - 1; i++) {
        stack[i] = stack[i + 1]; //shift index
        stack[i + 1] = 0; //zero clear
    }
    return temp;
}

/* clean the stack */
void clean(uint32_t* stack) {
    uint32_t i = 0;

    for (i = 0; i < STACK_DEAPTH; i++) {
        stack[i] = 0;
    }
}

/* fill the stack with specific value */
void fill(uint32_t value, uint32_t* stack) {
    uint32_t i = 0;

    for (i = 0; i < STACK_DEAPTH; i++) {
        stack[i] = value;
    }
}

/* show the existence of specific value in the stack in designated depth */
uint8_t exist(uint32_t value, uint32_t* stack, uint32_t depth) {
    uint32_t i = 0;

    for (i = 0; i < depth; i++) {
        if (stack[i] == value) {
            return 1;
        }
    }
    return 0;
}
