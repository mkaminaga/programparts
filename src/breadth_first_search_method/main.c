/*
 * Date:2015/02/01
 *
 * Q:How to search the best way form A to O?
 *
 *           A
 *          /|\
 *         / | \
 *        /  |  \
 *       B   C   D--.
 *      /|   |\   \  \
 *     / |   | \   \  \
 *    /  |   |  \   \  \
 *   E   F   G   H   I  J
 *      /|\      |\
 *     / | \     | \
 *    /  |  \    |  \
 *   K   L   M   N   O
 *
 * */

#include <stdio.h>
#include <stdint.h>

#define STACK_DEAPTH 255
#define QUE_DEPTH    255
#include "../../lib/stack.h"
#include "../../lib/que.h"

#define N 15

/*
 * In the node indicated by row, if you have branches to node indicated by
 * column, the value is 1.
 * If you don't have branch to the node, the value is 0.
 * */
const uint32_t adjacent[N][N] = {
  // 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14
  // A  B  C  D  E  F  G  H  I  J  K  L  M  N  O
    {0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // A 0
    {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // B 0
    {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, // C 2
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0}, // D 3
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // E 4
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0}, // F 5
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // G 6
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1}, // H 7
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // I 8
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // J 9
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // K 00
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // L 00
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // M 02
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, // N 03
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}  // O 04
};

#define EMPTY N + 1
int main(int argc, char const* argv[]) {

    /* stack for nodes linked to current node */
    uint32_t open[STACK_DEAPTH] = {EMPTY};

    /* array to memorize log */
    uint32_t log[STACK_DEAPTH] = {EMPTY};

    uint32_t node = EMPTY;
    int32_t i = 0;
    int32_t j = 0;

    /* set root node 'A' */
    put_que(0, open);

    for (i = 0; i < 50; i++) {

        /* get current node */
        node = take_out_que(open);

        /* exit status */
        if (node == EMPTY) {
            printf("%u: another route not found\n", i);
            return 0;
        }

        /* memorize log */
        push(node, log);

        /* goal status is 'O' */
        if (node == 14) {
            printf("route found\n");
            printf("log:");
            for (j = i; j >= 0; j--) {
                printf("%c%s", (log[j] + 'A'), ((j == 0) ? "." : "->"));
            }
            printf("\n\n");
            return 0;
        }

        /* check for all nodes linked to current node and add to the stack */
        for (j = 0; j < N; j++) {
            if (adjacent[node][j] == 1 && !exist(j, log, STACK_DEAPTH)) {
                put_que(j, open);
            }
        }
    }

    return 0;
}
