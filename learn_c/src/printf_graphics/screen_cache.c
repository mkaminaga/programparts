#include "main.h"

/* void clear_screen_cache()
 * fill chach eith background color.
 * arg1: pointer to the g_cache */
void clear_screen_cache(screen_cache_t* g_cache) {
    uint32_t x = 0;
    uint32_t y = 0;

    for (y = 0; y < Y_MAX; y++)
        for (x = 0; x < X_MAX; x++)
            g_cache->seg[y][x] = g_cache->bg;
}

/* void set_screen_cache(uint32_t, uint32_t, uint8_t)
 * set charactor on screen.
 * arg1: pointer to the g_cache
 * arg2: x cordinate of the point
 * arg3: y cordinate of the point
 * arg4: character to chach */
void set_screen_cache(screen_cache_t* g_cache, uint32_t x, uint32_t y, char c) {
    if (x >= X_MAX || x < 0) {
        printf("x out of range\n");
        return;
    }
    if (y >= Y_MAX || y < 0){
        printf("y out of range\n");
        return;
    }
    g_cache->seg[y][x] = c;
}

/* char get_screen_cache(screen_cache_t*, uint32_t, uint32_t)
 * get charactor g_cached in the screen
 * arg1: pointer to the chach
 * arg2: x cordinate of the point
 * arg3: y cordinate of the point */
char get_screen_cache(screen_cache_t* g_cache, uint32_t x, uint32_t y) {
    if (x >= X_MAX || x < 0) {
        printf("x out of range\n");
        return -1;
    }
    if (y >= Y_MAX || y < 0){
        printf("y out of range\n");
        return -1;
    }
    return g_cache->seg[y][x];
}

/* void flash_screen(screen_cache_t*)
 * output characters to screen g_cached in screen buffer.
 * arg1: pointer to the g_cache */
void flash_screen(screen_cache_t* g_cache) {
    uint32_t x = 0;
    uint32_t y = 0;

    /* draw all g_cache */
    for (y = 0; y < Y_MAX; y++) {
        for (x = 0; x < X_MAX; x++)
            printf("%c", g_cache->seg[y][x]);
        printf("\n");
    }
    printf("\n");
}

