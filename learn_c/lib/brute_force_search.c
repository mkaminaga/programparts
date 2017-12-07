#include <stdio.h>
#include <stdint.h>
#include "brute_force_search.h"

/* void brute_force_search(uint8_t[], uint32_t[], uint8_t[], uint32_t, uint32_t[], uint32_t*)
 * search a specific word in a text by brute force search.
 * arg1: text in whitch you search a word
 * arg2: the length of the text
 * arg3: string whitch you want to search
 * arg4: the length of the string
 * arg5: result of search, number of the string in text
 * arg6: result of search, index of hit string */
void boyer_moore_search(
        uint8_t text[], uint32_t text_len, uint8_t str[], uint32_t str_len,
        uint32_t* hit_num_p, uint32_t hit_index[]) {

    uint32_t i = 0;
    uint32_t j = 0;

    /* initialize hit counter */
    *hit_num_p = 0;

    i = 0;
    j = 0;

    while (i < text_len) {
        /* search string forward */
        if (text[i] == str[j]) {
            if (j == str_len - 1) {
                /* hit! */
                hit_index[*hit_num_p] = i - str_len + 1;
                *hit_num_p = *hit_num_p + 1;
                i = i - j + 1;
                j = 0;
            } else {
                i++;
                j++;
            }
        } else {
            i = i - j + 1;
            j = 0;
        }
    }
}
