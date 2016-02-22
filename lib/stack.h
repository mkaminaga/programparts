#ifndef STACK_H
#define STACK_H

#ifndef STACK_MAX
# define STACK_MAX 255
#endif

/* data type of array */
typedef uint32_t data_t;

typedef struct {
    data_t box[STACK_MAX];
    uint32_t top;
} stack_t;

/* void init_stack(stack_t*)
 * initialize pointer of stack.
 * arg1: pointer to the stack */
void init_stack(stack_t* s);

/* void push(stack_t*, data_t)
 * push to the stack.
 * arg1: pointer to the stack */
void push(stack_t* s, data_t data);

/* void pop(stack_t*)
 * pop from stack.
 * arg1: pointer to the stack */
void pop(stack_t* s);

/* data_t stack_is_empty(stack_t*)
 * return true when stack is empty.
 * arg1: pointer to the stack */
data_t stack_is_empty(stack_t* s);

/* data_t get_top_of_stack(stack_t*)
 * get top member of the stack.
 * arg1: pointer to the stack */
data_t get_top_of_stack(stack_t* s);

/* void show_inside_stack(stack_t*)
 * show stack elements for debug purpose.
 * arg1: pointer to the stack */
void show_inside_stack(stack_t* s);

#endif /* STACK_H */
