/* Date:2015/02/02 */
/* test my original que. */

#include <stdio.h>
#include <stdint.h>
#include "../lib/que.h"

#define QUE_DEPTH 255
uint32_t que[QUE_DEPTH] = {0};

int main(int argc, char const* argv[]) {
    put_que('A', que);
    printf("put_que A:%c\n", (char) que[0]);
    put_que('B', que);
    printf("put_que B:%c\n", (char) que[1]);
    put_que('C', que);
    printf("put_que C:%c\n", (char) que[2]);
    put_que('D', que);
    printf("put_que D:%c\n", (char) que[3]);
    put_que('F', que);
    printf("put_que F:%c\n", (char) que[4]);

    printf("take_out_que:%c\n", (char) take_out_que(que));
    printf("take_out_que:%c\n", (char) take_out_que(que));
    printf("take_out_que:%c\n", (char) take_out_que(que));
    printf("take_out_que:%c\n", (char) take_out_que(que));
    printf("take_out_que:%c\n", (char) take_out_que(que));
}
