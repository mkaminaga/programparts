#ifndef BRUTE_FORCE_SEARCH_METHOD_H
#define BRUTE_FORCE_SEARCH_METHOD_H

/* void brute_force_search(uint8_t[], uint32_t[], uint8_t[], uint32_t, uint32_t[], uint32_t*)
 * search a specific word in a text by brute force search.
 * arg1: text in whitch you search a word
 * arg2: the length of the text
 * arg3: string whitch you want to search
 * arg4: the length of the string
 * arg5: result of search, number of the string in text
 * arg6: result of search, index of hit string */
void boyer_moore_search( uint8_t text[], uint32_t text_len, uint8_t str[], uint32_t str_len, uint32_t* hit_num_p, uint32_t hit_index[]);

#endif /* BRUTE_FORCE_SEARCH_METHOD_H */
