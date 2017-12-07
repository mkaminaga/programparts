#include <stdio.h>
#include <stdint.h>
#include "stack.h"

/* void init_stack(stack_t*)
 * initialize pointer of stack.
 * arg1: pointer to the stack */
void init_stack(stack_t* s) {
    uint32_t i = 0;

    for (i = 0; i < STACK_MAX; i++) s->box[i] = 0;

    s->top = 0;
}

/* void push(stack_t*, data_t)
 * push to the stack.
 * arg1: pointer to the stack */
void push(stack_t* s, data_t data) {

    if (s->top >= STACK_MAX) return;

    s->top++; //shift index forward
    s->box[s->top] = data;
}

/* void pop(stack_t*)
 * pop from stack.
 * arg1: pointer to the stack */
void pop(stack_t* s) {

    if(stack_is_empty(s) == 1) return;

    s->top--; //shift index backward
}

/* data_t stack_is_empty(stack_t*)
 * return true when stack is empty.
 * arg1: pointer to the stack */
data_t stack_is_empty(stack_t* s) {
    return (s->top == 0); //if empty, true
}

/* data_t get_top_of_stack(stack_t*)
 * get top member of the stack.
 * arg1: pointer to the stack */
data_t get_top_of_stack(stack_t* s) {
    return s->box[s->top];
}

/* void show_inside_stack(stack_t*)
 * show stack elements for debug purpose.
 * arg1: pointer to the stack */
void show_inside_stack(stack_t* s) {
    uint32_t i = 0;

    for (i = 1; i <= (uint32_t) s->top; i++) printf("%u ", s->box[i]);
    printf("\n");
}
