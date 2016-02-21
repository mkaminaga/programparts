/* Date:2015/02/02 */
/* test queue. */

#include <stdio.h>
#include <stdint.h>
#include "../../lib/list.h"

element_t* list_p;

int main(int argc, char const* argv[]) {
    int32_t i = 0;

    /* initialize list */
    printf("init\n");
    if (init_list(list_p) == NULL) {
        printf("memory allocation failed\n");
    }

#if 0
    /* add elements to the list */
    printf("add\n");
    for (i = 0; i < 'G' - 'A'; i++) {
        add_to_list(&list, i + 'A');
        show_inside_of_list(&list);
    }
    printf("\n");

    /* delete form list */
    printf("delete\n");
    for (i = 'G' - 'A' + 1; i >= 0; i++) {
        delete_from_list(&list, i);
        show_inside_of_list(&list);
    }
    printf("\n");
#endif

    /* free list */
    printf("free\n");
    free_list(list_p);
}
