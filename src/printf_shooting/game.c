#include "main.h"

/* void draw_static_wall()
 * draw wall. */
void draw_static_wall() {
    /* wall data */
    const char wall[Y_MAX][X_MAX] = {
        {' ','+','+','+','+','+','+','+','+','+','+','+','+','+','+'},
        {' ','+',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','+'},
        {'+','+',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','+'},
        {'+',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','+'},
        {'+',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','+','+'},
        {'+',' ',' ',' ',' ',' ',' ','+','+','+','+','+','+','+',' '},
        {'+','+','+','+','+','+','+','+',' ',' ',' ',' ',' ',' ',' '}
    };

    uint32_t x = 0;
    uint32_t y = 0;

    /* set wall */
    for (y = 0; y < Y_MAX; y++)
        for (x = 0; x < X_MAX; x++)
            set_screen_cache(&g_cache, x, y, wall[y][x]);
}

/* void draw_moving_wall(ball_t*)
 * draw moving wall. */
void draw_moving_wall() {
    /* x way moving wall difinition */
    typedef struct {
        uint32_t x;
        uint32_t y;
        int32_t vx;
        char str[4];
    } x_move_wall_t;

    static x_move_wall_t s_x_wall = {
        4, 3, 1, "---"
    };

    /* movement */
    s_x_wall.x += s_x_wall.vx;

    /* collision judgement */
    if (s_x_wall.vx > 0) {
        /* right edge collison */
        if (get_screen_cache(&g_cache, s_x_wall.x + s_x_wall.vx + 2, s_x_wall.y) == '+')
             s_x_wall.vx *= -1;
    } else {
        /* left edge collison */
        if (get_screen_cache(&g_cache, s_x_wall.x + s_x_wall.vx, s_x_wall.y) == '+')
             s_x_wall.vx *= -1;
    }

    /* draw */
    set_screen_cache(&g_cache, s_x_wall.x, s_x_wall.y, s_x_wall.str[0]);
    set_screen_cache(&g_cache, s_x_wall.x + 1, s_x_wall.y, s_x_wall.str[1]);
    set_screen_cache(&g_cache, s_x_wall.x + 2, s_x_wall.y, s_x_wall.str[2]);
}

/* void control_ball(ball_t*)
 * draw ball bounding on wall. */
void control_ball() {
    /* charactor data definition */
    typedef struct {
        uint32_t x;
        uint32_t y;
        int32_t vx;
        int32_t vy;
        char c;
    } ball_t;

    static ball_t s_ball;
    static uint8_t s_first_flag = 1;

    /* initialize s_ball */
    if (s_first_flag == 1) {
        s_ball.x = 6;
        s_ball.y = 4;
        s_ball.vx = 1;
        s_ball.vy = -1;
        s_ball.c = '*';
        s_first_flag = 0;
    }

    /* movement */
    s_ball.x += s_ball.vx;
    s_ball.y += s_ball.vy;

    /* collision judgement */
    if (get_screen_cache(&g_cache, s_ball.x + s_ball.vx, s_ball.y) != ' ')
        s_ball.vx *= -1;
    if (get_screen_cache(&g_cache, s_ball.x, s_ball.y + s_ball.vy) != ' ')
        s_ball.vy *= -1;

    /* draw */
    set_screen_cache(&g_cache, s_ball.x, s_ball.y, s_ball.c);
}
