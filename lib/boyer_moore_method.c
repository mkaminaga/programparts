#include <stdio.h>
#include <stdint.h>
#include "boyer_moore_method.h"

/* uint32_t max(uint32_t, uint32_t)
 * returns largear one from given two arguments
 * arg1: value1
 * arg2: value2 */
uint32_t max(uint32_t a, uint32_t b);

/* void boyer_moore_search(uint8_t[], uint32_t[], uint8_t[], uint32_t, uint32_t[], uint32_t*)
 * search a specific word in a text by boyer moore method.
 * arg1: text in whitch you search a word
 * arg2: the length of the text
 * arg3: string whitch you want to search
 * arg4: the length of the string
 * arg5: result of search, number of the string in text
 * arg6: result of search, index of hit string */
void boyer_moore_search(
        uint8_t text[], uint32_t text_len, uint8_t str[], uint32_t str_len,
        uint32_t* hit_num_p, uint32_t hit_index[] ) {

    uint32_t skip[256];
    uint32_t i = 0;
    uint32_t j = 0;

    /* gnerate skip list with ascii index */
    for (i = 0; i < 255; i++) skip[i] = str_len;
    for (i = 0; i < str_len - 1; i++) skip[str[i]] = str_len - i - 1;

    /* initialize hit counter */
    *hit_num_p = 0;

    for (i = str_len - 1; i < text_len; i += max(skip[text[i]], str_len - j)) {

        /* search string backward */
        for (j = str_len - 1; text[i] == str[j]; i--, j--) {
            if (j == 0) {
                /* hit! */
                hit_index[*hit_num_p] = i;
                *hit_num_p = *hit_num_p + 1;
                break;
            }
        }
    }
}

/* uint32_t max(uint32_t, uint32_t)
 * returns largear one from given two arguments
 * arg1: value1
 * arg2: value2 */
uint32_t max(uint32_t a, uint32_t b) {
    if (a > b) return a;
    return b;
}
