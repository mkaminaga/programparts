/*
 * Date:2015/02/01
 * reference:http://www.geocities.jp/m_hiroi/puzzle/puzdoc01.html
 *
 * Q:How to get to G from A?
 *
 *    B----D----F
 *   /|    |
 *  A |    |
 *   \|    |
 *    C----E----G
 *
 * */

#include <stdio.h>
#include <stdint.h>

#define STACK_DEAPTH 255
#include "../lib/stack.h"

#define N 7

const uint32_t adjacent[N][N] = {
  //0  1  2  3  4  5  6
  //A  B  C  D  E  F  G
    {0, 1, 1, 0, 0, 0, 0}, // A 0
    {1, 0, 1, 1, 0, 0, 0}, // B 1
    {1, 1, 0, 0, 1, 0, 0}, // C 2
    {0, 1, 0, 0, 1, 1, 0}, // D 3
    {0, 0, 1, 1, 0, 0, 1}, // E 4
    {0, 0, 0, 1, 0, 0, 0}, // F 5
    {0, 0, 0, 0, 1, 0, 0}  // G 6
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

NEXT_PATH:

    /* set root node */
    fill(EMPTY, open);
    push(0, open);

    for (i = 0; i < 20; i++) {

        /* get current node */
        node = pop(open);

        /* exit status */
        if (node == EMPTY) {
            printf("path not found\n");
            return 0;
        }

        /* memorize path */
        push(node, path);

        /* 4. goal status */
        if (node == 6) {
            printf("path found\n");
            printf("trial:%u\n", i);
            for (j = i; j >= 0; j--) printf("%c ", (path[j] + 'A'));
            printf("\n");

            push(node, open);
            goto NEXT_PATH;
        }

        /* 5. check for all nodes linked to current node and add to the stack */
        for (j = 0; j < N; j++) {
            if (adjacent[node][j] == 1 && !exist(j, path, STACK_DEAPTH)) {
                push(j, open);
            }
        }
    }

    return 0;
}
