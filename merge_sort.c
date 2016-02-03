#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const* argv[]) {

#define DATA_SIZE 13
    /* test */
    printf("/* test */\n");
    /* uint32_t cards[DATA_SIZE] = */
    /*     {'1', '2', '3', '4', '5', '6', '7' '8', '9', '10', 'J', 'Q', 'K'}; */

    uint32_t index[DATA_SIZE][2] = {-1};
    uint32_t len = DATA_SIZE;
    uint32_t rayer = 0;
    uint32_t i = 0;

    rayer = 1;
    len = DATA_SIZE;

    for (i = 0; i < 3; i++) {
        if (len > 1) {
            if (len % 2 == 0) {
                len = len / 2;
                index[i][0] = len / 2;
            } else {
                len = len / 2 + 1;
                index[i][0] = len / 2 + 1;
            }
            len = index[rayer][]
            rayer++;
        }

        printf("%u, %u\n", index[i][0], index[rayer][1]);
    }

    return 0;
}
