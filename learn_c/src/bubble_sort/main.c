#include <stdio.h>
#include <stdint.h>
#include "../../lib/bubble_sort.h"

int main(int argc, char const* argv[]) {

    data_t data[] = {
        0, 8, 1, 3, 5, 4, 9, 7, 2, 6
    };

    printf("before:%u ,%u ,%u ,%u ,%u ,%u ,%u ,%u ,%u ,%u\n",
        data[0], data[1], data[2], data[3], data[4],
        data[5], data[6], data[7], data[8], data[9]);

    bubble_sort(data, 10);

    printf("after: %u ,%u ,%u ,%u ,%u ,%u ,%u ,%u ,%u ,%u\n",
        data[0], data[1], data[2], data[3], data[4],
        data[5], data[6], data[7], data[8], data[9]);
    printf("\n");

    return 0;
}
