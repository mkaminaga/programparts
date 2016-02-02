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

uint32_t open[STACK_DEAPTH] = {0};
uint32_t close[STACK_DEAPTH] = {0};

int main(int argc, char const* argv[]) {
    uint8_t i = 0;

    for (i = 0; i < N; i++) {
        if (adjacent[0][i] == 1) {
            push(i, open);
        }
    }

    for (i = 0; i < N; i++) printf("%u ", open[i]);
    printf("\n");
}
