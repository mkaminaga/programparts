#include <stdio.h>
#include <stdint.h>

/* sort given data.
 * arg1: given data
 * arg2: ascending(=1) and decending(=0)
 * arg3: depth of index to be sorted
 * */
void bubble_sort(uint32_t data[], uint8_t way, uint32_t depth);

int main(int argc, char const* argv[]) {
    uint32_t data[] = { 0, 8, 1, 3, 5, 4, 9, 7, 2, 6 };

    /* ascending order */
    printf("index 0 ~ 9, ascending:\n");
    printf("before:%u ,%u ,%u ,%u ,%u ,%u ,%u ,%u ,%u ,%u\n",
        data[0], data[1], data[2], data[3], data[4],
        data[5], data[6], data[7], data[8], data[9]);

    bubble_sort(data, 1, 10);

    printf("after: %u ,%u ,%u ,%u ,%u ,%u ,%u ,%u ,%u ,%u\n",
        data[0], data[1], data[2], data[3], data[4],
        data[5], data[6], data[7], data[8], data[9]);
    printf("\n");

    /* decending order */
    printf("index 0 ~ 9, decending:\n");
    printf("before:%u ,%u ,%u ,%u ,%u ,%u ,%u ,%u ,%u ,%u\n",
        data[0], data[1], data[2], data[3], data[4],
        data[5], data[6], data[7], data[8], data[9]);

    bubble_sort(data, 0, 10);

    printf("after: %u ,%u ,%u ,%u ,%u ,%u ,%u ,%u ,%u ,%u\n",
        data[0], data[1], data[2], data[3], data[4],
        data[5], data[6], data[7], data[8], data[9]);
    printf("\n");

    /* ascending order */
    printf("index 0 ~ 4, ascending:\n");
    printf("before:%u ,%u ,%u ,%u ,%u ,%u ,%u ,%u ,%u ,%u\n",
        data[0], data[1], data[2], data[3], data[4],
        data[5], data[6], data[7], data[8], data[9]);

    bubble_sort(data, 1, 5);

    printf("after: %u ,%u ,%u ,%u ,%u ,%u ,%u ,%u ,%u ,%u\n",
        data[0], data[1], data[2], data[3], data[4],
        data[5], data[6], data[7], data[8], data[9]);
    printf("\n");

    /* decending order */
    printf("index 0 ~ 4, decending:\n");
    printf("before:%u ,%u ,%u ,%u ,%u ,%u ,%u ,%u ,%u ,%u\n",
        data[0], data[1], data[2], data[3], data[4],
        data[5], data[6], data[7], data[8], data[9]);

    bubble_sort(data, 0, 5);

    printf("after: %u ,%u ,%u ,%u ,%u ,%u ,%u ,%u ,%u ,%u\n",
        data[0], data[1], data[2], data[3], data[4],
        data[5], data[6], data[7], data[8], data[9]);

    return 0;
}

/* sort given data.
 * arg1: given data
 * arg2: ascending(=1) and decending(=0)
 * arg3: depth of index to be sorted
 * */
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


