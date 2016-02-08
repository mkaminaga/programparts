/*
 * Date:2015/02/01
 *
 * Q:How to EXIT_BRANCH the way form A to O?
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
#include <unistd.h>

#define QUE_DEPTH    255
#include "../../lib/queue.h"

#define N ('O' - 'A' + 1)

/*
 * In the node indicated by row, if you have branches to node indicated by
 * column, the value is 1.
 * If you don't have branch to the node, the value is 0.
 * */
const uint32_t adjacent[N][N] = {
  // 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14
  // A  B  C  D  E  F  G  H  I  J  K  L  M  N  O
    {0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // A  0
    {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // B  0
    {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, // C  2
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0}, // D  3
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // E  4
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0}, // F  5
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // G  6
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1}, // H  7
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // I  8
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // J  9
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // K 10
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // L 10
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // M 12
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, // N 13
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}  // O 14
};

int main(int argc, char const* argv[]) {

    /* stack for nodes linked to current node */
    queue_t open;

    /* array for log */
    uint32_t log[QUE_DEPTH];
    uint32_t log_i = 0;

    uint32_t node = 0;
    uint32_t flag = 0;
    uint32_t i = 0;
    uint32_t j = 0;

    /* initialize queue */
    init_queue(&open);

    /* set root node 'A' */
    insert(&open, 'A');

    for (;;) {
        /* show process */
        printf("%2u:", log_i);
        for (i = 0; i < log_i; i++) {
            printf("%c%s", (char) log[i], ((i == log_i - 1) ? "\n":"->"));
        }
        if (log_i == 0) printf("\n");

        if (node == 'O') {
            printf("route found\n");
            return 0;
        }

        /* get current node */
        node = get_top_of_queue(&open);
        take_out(&open);

        usleep(5E5);

        /* take log */
        log[log_i] = node;
        log_i++;

        /* search fail */
        if (node == 0) {
            printf("route not found\n");
            return 0;
        }

        /* check for all nodes linked to current node and add to the queue */
        for (i = 0; i < N; i++) {
            flag = 1;
            /* skip node already registerd in queue */
            for (j = open.head; j <= open.tail; j++) {
                if (open.box[j] == i + 'A') flag = 0;
            }
            if (adjacent[node - 'A'][i] == 1 && flag == 1) {
                insert(&open, i + 'A');
            }
        }
    }

    return 0;
}
