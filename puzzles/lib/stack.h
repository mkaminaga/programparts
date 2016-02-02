#ifndef STACK_H
#define STACK_H

/* user stack size. default is 255 */
#ifndef STACK_DEAPTH
# define STACK_DEAPTH 255
#endif

/* push to stack. stack size can be changed by STACK_DEAPTH */
void push(uint32_t node, uint32_t* stack);

/* pop from stack. stack size can be changed by STACK_DEAPTH */
uint32_t pop(uint32_t* stack);

#endif /* STACK_H */
