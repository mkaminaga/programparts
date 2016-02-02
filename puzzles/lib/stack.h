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

/* clean the stack */
void clean(uint32_t* stack);

/* fill the stack with specific value */
void fill(uint32_t value, uint32_t* stack);

/* show the existence of specific value in the stack in designated depth */
uint8_t exist(uint32_t value, uint32_t* stack, uint32_t depth);

#endif /* STACK_H */
