/* Date:2015/02/09 */
/* test heap. */
#include <stdio.h>
#include <stdint.h>

#define HEAP_MAX 255
#include "../../lib/heap.h"

heap_t heap;

int main(int argc, char const* argv[]) {
    int32_t i = 0;

    /* init stack */
    init_heap(&heap);

    /* push stack */
    for (i = 'G' - 'A'; i >= 0; i--) {
        insert_to_heap(&heap, i + 'A');
        show_inside_heap(&heap);
    }

    /* pop stack */
    for (i = 0; i < 'G' - 'A'; i++) {
        delete_min_of_heap(&heap);
        show_inside_heap(&heap);
    }
}
