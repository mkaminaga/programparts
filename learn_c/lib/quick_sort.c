#include <stdio.h>
#include <stdint.h>
#include "stack.h"
#include "merge_sort.h"

#if defined(DEBUG)
#include <unistd.h>
#endif

/* void set_parts(data_t, uint32_t, uint32_t*, uint32_t)
 * diveide array A into A1 and A2.
 * A1 has members same or smaller than A[0].
 * A2 has members same or larger than A[0].
 * arg1: pointer to the data array
 * arg2: A's index 0 (smaller's partial head)
 * arg3: A's index max (larger part's tail)
 * arg4: solution, smaller part's tail
 * arg5, solution, larger part's head */
void set_parts(data_t a[], uint32_t head, uint32_t tail,
        uint32_t* ss_tail_p, uint32_t* ls_head_p);

/* void quick_sort(data_t[], uint32_t)
 * sort data by quick sort algolthm.
 * arg1: pointer to the data array
 * arg2: data array length */
void quick_sort(data_t a[], uint32_t length) {

    stack_t stack;
    uint32_t ss_tail = 0;
    uint32_t ls_head = 0;
    uint32_t head = 0;
    uint32_t tail = 0;

    /* initialize stack */
    init_stack(&stack);

    /* set initial pare */
    push(&stack, length - 1); //tail
    push(&stack, 0); //head

    while (!stack_is_empty(&stack)) {

        /* get next pare */
        head = get_top_of_stack(&stack);
        pop(&stack);
        tail = get_top_of_stack(&stack);
        pop(&stack);

        /* process parts */
        set_parts(a, head, tail, &ss_tail, &ls_head);

#if defined(DEBUG)
        uint32_t k = 0;

        /* all */
        for (k = 0; k < length; k++) printf("%u ", a[k]);
        printf("\n");

        /* small fraction */
        printf("ss:%u-%u:", head, ss_tail);
        for (k = head; k <= ss_tail; k++) printf("%u ", a[k]);
        printf("\n");

        /* large fraction */
        printf("ls:%u-%u:", ls_head, tail);
        for (k = ls_head; k <= tail; k++) printf("%u ", a[k]);
        printf("\n");

        printf("\n");
        usleep(5E5);
#endif

        if (head < ss_tail) {
            push(&stack, ss_tail);
            push(&stack, head);
        }

        if (ls_head < tail) {
            push(&stack, tail);
            push(&stack, ls_head);
        }
    }
}

/* void set_parts(data_t, uint32_t, uint32_t*, uint32_t)
 * diveide array A into A1 and A2.
 * A1 has members same or smaller than A[0].
 * A2 has members same or larger than A[0].
 * arg1: pointer to the data array
 * arg2: A's index 0 (smaller's partial head)
 * arg3: A's index max (larger part's tail)
 * arg4: solution, smaller part's tail
 * arg5, solution, larger part's head */
void set_parts(data_t a[], uint32_t head, uint32_t tail,
        uint32_t* ss_tail_p, uint32_t* ls_head_p) {

    uint32_t i = 0; //start from ls
    uint32_t j = 0; //start from rs
    uint32_t temp = 0; //swap bucket

    i = head;
    j = tail;

    while (i <= j) {

        while (a[i] < a[head]) i++; //go foward
        while (a[j] > a[head]) j--; //go backward

        /* swap */
        if (i <= j) {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i++;
            j--;
        }
    }

    *ss_tail_p = j;
    *ls_head_p = i;
}
