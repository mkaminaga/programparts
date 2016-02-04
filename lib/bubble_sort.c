#include <stdio.h>
#include <stdint.h>

/* sort given data.
 * arg1: given data
 * arg2: ascending(=1) and decending(=0)
 * arg3: depth of index to be sorted */
void bubble_sort(uint32_t data[], uint8_t way, uint32_t depth) {
    uint8_t end_flag = 1;
    uint32_t i = 0;
    uint32_t temp = 0;

    /* exception */
    if (depth < 1) {
        return;
    }

    end_flag = 0;

    while (end_flag == 0) {
        end_flag = 1;

        if (way == 1) {
            /* ascending order */
            for (i = 0; i < depth - 1; i++) {
                if(data[i] > data[i + 1]) {
                    temp = data[i + 1];
                    data[i + 1] = data[i];
                    data[i] = temp;
                    end_flag = 0;
                }
            }
        } else {
            /* decending order */
            for (i = 0; i < depth - 1; i++) {
                if(data[i] < data[i + 1]) {
                    temp = data[i + 1];
                    data[i + 1] = data[i];
                    data[i] = temp;
                    end_flag = 0;
                }
            }
        }
    }
}

/* sort given data.
 * arg1: given data
 * arg2: key of sorting
 * arg2: ascending(=1) and decending(=0)
 * arg3: depth of index to be sorted */
void bubble_sort_2d(
        uint32_t data[][2], uint8_t key, uint8_t way, uint32_t depth) {
    uint8_t end_flag = 1;
    uint32_t i = 0;
    uint32_t temp = 0;
    uint32_t temp2 = 0;

    /* exception */
    if (depth < 1) {
        return;
    }

    end_flag = 0;

    while (end_flag == 0) {
        end_flag = 1;

        if (way == 1) {
            /* ascending order */
            for (i = 0; i < depth - 1; i++) {
                if(data[i][key] > data[i + 1][key]) {
                    temp = data[i + 1][0];
                    temp2 = data[i + 1][1];
                    data[i + 1][0] = data[i][0];
                    data[i + 1][1] = data[i][1];
                    data[i][0] = temp;
                    data[i][1] = temp2;
                    end_flag = 0;
                }
            }
        } else {
            /* decending order */
            for (i = 0; i < depth - 1; i++) {
                if(data[i][key] < data[i + 1][key]) {
                    temp = data[i + 1][0];
                    temp2 = data[i + 1][1];
                    data[i + 1][0] = data[i][0];
                    data[i + 1][1] = data[i][1];
                    data[i][0] = temp;
                    data[i][1] = temp2;
                    end_flag = 0;
                }
            }
        }
    }
}

