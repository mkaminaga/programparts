#include <stdio.h>
#include <stdint.h>
#include "que.h"

static uint32_t s_que_index = 0;

/* put que. que size can be changed by QUE_DEPTH */
void put_que(uint32_t node, uint32_t* que) {
    que[s_que_index] = node;
    s_que_index++;
}

/* take out que. que size can be changed by QUE_DEPTH */
uint32_t take_out_que(uint32_t* que) {
    uint32_t i = 0;
    uint32_t temp = 0;

    temp = que[0];
    for (i = 0; i < QUE_DEPTH - 1; i++) {
        que[i] = que[i + 1]; //shift foward
        que[i + 1] = 0; //zero clear tail
    }

    s_que_index--;
    return temp;
}

/* clean the que */
void clean_que(uint32_t* que) {
    uint32_t i = 0;

    for (i = 0; i < QUE_DEPTH; i++) {
        que[i] = 0;
    }

    s_que_index = 0;
}

/* fill the que with specific value */
void fill_que(uint32_t value, uint32_t* que) {
    uint32_t i = 0;

    for (i = 0; i < QUE_DEPTH; i++) {
        que[i] = value;
    }

    s_que_index = 0;
}

/* show the existence of specific value in the que in designated depth */
uint8_t exist_in_que(uint32_t value, uint32_t* que, uint32_t depth) {
    uint32_t i = 0;

    for (i = 0; i < depth; i++) {
        if (que[i] == value) {
            return 1;
        }
    }
    return 0;
}

