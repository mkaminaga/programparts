#include <stdio.h>
#include <stdint.h>
#include "stack.h"
#include "merge_sort.h"

#if defined(DEBUG)
#include <unistd.h>
#endif

/* void qsort_dig(uint32_t, uint32_t, uint32_t*, uint32_t)
 * diveide array A into A1 and A2.
 * A1 has members same or smaller than A[0].
 * A2 has members same or larger than A[0].
 * arg1: pointer to the data array
 * arg2: A's index 0 (smaller's partial head)
 * arg3: A's index max (larger part's tail)
 * arg4: solution, smaller part's tail
 * arg5, solution, larger part's head */
void qsort_dig(uint32_t a[], uint32_t head, uint32_t tail,
        uint32_t* ss_tail_p, uint32_t* ls_head_p);

/* void quick_sort(uint32_t[], uint32_t)
 * sort data by quick sort algolthm.
 * arg1: pointer to the data array
 * arg2: data array length */
void quick_sort(uint32_t a[], uint32_t length) {

    stack_t stack;

    uint32_t i = 0;
    uint32_t j = 0;
    uint32_t head = 0;
    uint32_t tail = 0;

    /* initialize stack */
    init_stack(&stack);

    /* set initial pare */
    push(&stack, length - 1); //tail
    push(&stack, 0); //head

    while (!stack_is_empty(&stack)) {

#if defined(DEBUG)
        for (uint32_t k = 0; k < length; k++)
            printf("%u ", a[k]);
        printf("\n");
        /* show_inside_stack(&stack); */
        usleep(5E5);
#endif

        /* get next pare */
        head = get_top_of_stack(&stack);
        pop(&stack);
        tail = get_top_of_stack(&stack);
        pop(&stack);

        /* process parts */
        qsort_dig(a, head, tail, &i, &j);

        if (head < j) {
            push(&stack, j);
            push(&stack, head);
        }

        if (i < tail) {
            push(&stack, tail);
            push(&stack, i);
        }
    }
}

/* void qsort_dig(uint32_t, uint32_t, uint32_t*, uint32_t)
 * diveide array A into A1 and A2.
 * A1 has members same or smaller than A[0].
 * A2 has members same or larger than A[0].
 * arg1: pointer to the data array
 * arg2: A's index 0 (smaller's partial head)
 * arg3: A's index max (larger part's tail)
 * arg4: solution, smaller part's tail
 * arg5, solution, larger part's head */
void qsort_dig(uint32_t a[], uint32_t head, uint32_t tail,
        uint32_t* ss_tail_p, uint32_t* ls_head_p) {

    int32_t i = 0;
    int32_t j = 0;
    uint32_t thr = 0; //threshold value
    uint32_t temp = 0; //swap bucket

    thr = a[head];
    i = head;
    j = tail;

    while (i <= j) {

#if defined(DEBUG)
        printf("i:%u, j:%u\n", i, j);
#endif

        while (a[i] < thr) i++; //go foward
        while (a[j] > thr) j--; //go backward

        /* swap */
        if (i <= j) {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i++;
            j--;
        }
    }

    *ss_tail_p = i;
    *ls_head_p = j;
}
