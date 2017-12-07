#include "main.h"

screen_cache_t g_cache;

int main() {

    /* init cache */
    g_cache.bg = ' ';
    g_cache.fg = '+';

    for (;;) {
        /* clear cache */
        clear_screen_cache(&g_cache);

        /* draw static wall */
        draw_static_wall();

        /* draw moving wall */
        draw_moving_wall();

        /* draw ball */
        control_ball();

        /* draw on the screen */
        flash_screen(&g_cache);

        /* speed adjustment */
        usleep(1E5); //0.1sec
    }

    return 0;
}
