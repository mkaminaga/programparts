#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "../../lib/boyer_moore_method.h"

int main() {
    uint8_t text[] = "This is a test of word searching. Have a nice year!";
    uint32_t text_len = sizeof(text) - 1;
    uint8_t string[] = "ear";
    uint32_t str_len = sizeof(string) - 1;
    uint32_t hit_index[255];
    uint32_t hit_num = 0;
    uint32_t i = 0;

    /* show condition */
    printf("text    : %s\n", text);
    printf("text_len: %u\n", text_len);
    printf("string  : %s\n", string);
    printf("str_len : %u\n", str_len);
    printf("\n");

    /* execute search */
    boyer_moore_search(text, text_len, string, str_len, &hit_num, hit_index);

    /* show result */
    printf("hit_num : %u\n", hit_num);
    for (i = 0; i < hit_num; i++)
        printf("hit_index[%u] = %u\n", i, hit_index[i]);

   return 0;
}
