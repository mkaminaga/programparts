#ifndef SCREEN_CACHE_H
#define SCREEN_CACHE_H

#ifndef Y_MAX
# define Y_MAX 50
#endif

#ifndef X_MAX
# define X_MAX 100
#endif

typedef struct {
    uint32_t seg[Y_MAX][X_MAX];
    uint32_t bg;
    uint32_t fg;
} screen_cache_t;

/* void clear_screen_cache()
 * fill chach eith background color.
 * arg1: pointer to the cache */
void clear_screen_cache(screen_cache_t* cache);

/* void set_screen_cache(uint32_t, uint32_t, uint8_t)
 * set charactor on screen.
 * arg1: pointer to the cashe
 * arg2: x cordinate of the point
 * arg3: y cordinate of the point
 * arg4: character to chach */
void set_screen_cache(screen_cache_t* cashe, uint32_t x, uint32_t y, char c);

/* char get_screen_cache(screen_cache_t*, uint32_t, uint32_t)
 * get charactor cached in the screen
 * arg1: pointer to the chach
 * arg2: x cordinate of the point
 * arg3: y cordinate of the point */
char get_screen_cache(screen_cache_t* cashe, uint32_t x, uint32_t y);

/* void flash_screen(screen_cache_t*)
 * output characters to screen cached in screen buffer.
 * arg1: pointer to the cache */
void flash_screen(screen_cache_t* cashe);

#endif /* SCREEN_CACHE_H */
