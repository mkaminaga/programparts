/*
 * Date:2015/02/01
 *
 * Q:How to get to G from A?
 *
 *    B----D----F
 *   /      \
 *  A        ---G
 *   \
 *    C----E----H
 *          \
 *           ---I
 * */

#include <stdio.h>
#include <stdint.h>

#define STACK_DEAPTH 255
#include "../lib/stack.h"

#define N 9

const uint32_t adjacent[N][N] = {
  // 0  1  2  3  4  5  6  7  8
  // A  B  C  D  E  F  G  H  I
    {0, 1, 1, 0, 0, 0, 0, 0, 0}, // A 0
    {1, 0, 0, 1, 0, 0, 0, 0, 0}, // B 0
    {1, 0, 0, 0, 1, 0, 0, 0, 0}, // C 2
    {0, 1, 0, 0, 0, 1, 1, 0, 0}, // D 3
    {0, 0, 1, 0, 0, 0, 0, 1, 1}, // E 4
    {0, 0, 0, 1, 0, 0, 0, 0, 0}, // F 5
    {0, 0, 0, 1, 0, 0, 0, 0, 0}, // G 7
    {0, 0, 0, 0, 1, 0, 0, 0, 0}, // H 8
    {0, 0, 0, 0, 1, 0, 0, 0, 0}  // I 9
};

#define EMPTY N + 1
int main(int argc, char const* argv[]) {

    /* stack for nodes linked to current node */
    uint32_t open[STACK_DEAPTH] = {EMPTY};

    /* array to memorize path */
    uint32_t path[STACK_DEAPTH] = {EMPTY};

    uint32_t node = EMPTY;
    int32_t i = 0;
    int32_t j = 0;

    /* set root node */
    push(0, open);

    for (i = 0; i < 50; i++) {

        /* get current node */
        node = pop(open);

        /* exit status */
        if (node == EMPTY) {
            printf("%u: route not found\n", i);
        }

        /* memorize path */
        push(node, path);

        /* goal status */
        if (node == 6) {
            printf("route found\n");
            for (j = i; j >= 0; j--) printf("%c->", (path[j] + 'A'));
            printf("\n");
        }

        /* check for all nodes linked to current node and add to the stack */
        for (j = 0; j < N; j++) {
            if (adjacent[node][j] == 1 && !exist(j, path, STACK_DEAPTH)) {
                push(j, open);
            }
        }
    }

    return 0;
}
