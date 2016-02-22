/* Date:2015/02/02 */
/* test queue. */

#include <stdio.h>
#include <stdint.h>
#include "../../lib/list.h"

element_t* list_p;

int main(int argc, char const* argv[]) {
    int32_t i = 0;

    /* null definition on your patform */
    printf("NULL = %p\n", NULL);

    /* initialize list */
    printf("init\n");
    init_list(&list_p);

    /* add 6 elements to the list */
    printf("add 0 to 5\n");
    for (i = 0; i < 6; i++) {
        add_to_list(list_p, i + 'A');
        show_inside_of_list(list_p);
    }
    printf("\n");

    /* delete specific index form list */
    printf("delete index 2\n");
    delete_from_list(list_p, 2);
    show_inside_of_list(list_p);
    printf("\n");

    /* insert specific index to list */
    printf("insert to index 3\n");
    insert_to_list(list_p, 3, 'A');
    show_inside_of_list(list_p);
    printf("\n");

    /* free list */
    printf("free all\n");
    free_list(list_p);
}
