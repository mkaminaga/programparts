#include <stdio.h>
#include <stdint.h>
#include "bubble_sort.h"

/* sort given data.
 * arg1: given data
 * arg3: length of array to be sorted */
void bubble_sort(data_t data[], uint32_t length) {
    uint8_t end_flag = 1;
    uint32_t i = 0;
    uint32_t temp = 0;

    end_flag = 0;
    while (end_flag == 0) {
        end_flag = 1;

        for (i = 0; i < length - 1; i++) {
            if(data[i] > data[i + 1]) {
                temp = data[i + 1];
                data[i + 1] = data[i];
                data[i] = temp;
                end_flag = 0;
            }
        }
    }
}
