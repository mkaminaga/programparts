#include "main.h"

/* void draw_static_wall()
 * draw wall. */
void draw_static_wall() {
    /* wall data */
    const char wall[Y_MAX][X_MAX] = {
        {' ',' ',' ',' ',' ',' ','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+'},
        {' ',' ',' ',' ','+','+','+',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','+'},
        {' ',' ','+','+','+',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','+'},
        {' ','+','+',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','+'},
        {'+','+',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','+'},
        {'+',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','+','+','+','+','+','+',' ',' ',' ',' ',' ',' ',' ','+','+','+','+','+','+'},
        {'+',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','+',' ',' ',' ',' ','+',' ',' ',' ',' ',' ',' ',' ','+',' ',' ',' ',' ',' '},
        {'+',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','+',' ',' ',' ',' ','+',' ',' ',' ',' ',' ',' ',' ','+',' ',' ',' ',' ',' '},
        {'+',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','+','+','+','+','+','+',' ',' ',' ',' ',' ',' ',' ','+',' ',' ',' ',' ',' '},
        {'+',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','+','+','+','+',' ',' '},
        {'+',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','+','+','+'},
        {'+',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','+'},
        {'+',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','+'},
        {'+',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','+'},
        {'+',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','+'},
        {'+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+','+'}
    };

    uint32_t x = 0;
    uint32_t y = 0;

    /* set wall */
    for (y = 0; y < Y_MAX; y++)
        for (x = 0; x < X_MAX; x++)
            set_screen_cache(&g_cache, x, y, wall[y][x]);
}


#define X_WALL_NUM 5

/* void draw_moving_wall(ball_t*)
 * draw moving wall. */
void draw_moving_wall() {

    /* x way moving wall difinition */
    typedef struct {
        uint32_t x;
        uint32_t y;
        int32_t vx;
        int32_t vy;
        char str[4];
    } move_wall_t;

    uint32_t i = 0;
    static uint8_t s_first_flag = 1;
    static move_wall_t s_x_walls[X_WALL_NUM];

    /* set movement of walls */
    for (i = 0; i < X_WALL_NUM; i++) {
        if (s_first_flag == 1) {
            s_x_walls[i].x = 5 * i + 5;
            s_x_walls[i].y = 3 * i + 2;
            s_x_walls[i].vx = 1;
            s_x_walls[i].str[0] = '-';
            s_x_walls[i].str[1] = '-';
            s_x_walls[i].str[2] = '-';
        }

        /* movement */
        s_x_walls[i].x += s_x_walls[i].vx;

        /* collision judgement */
        if (s_x_walls[i].vx > 0) {
            /* right edge collison */
            if (get_screen_cache(
                    &g_cache,
                    s_x_walls[i].x + s_x_walls[i].vx + 2, s_x_walls[i].y)
                    == '+')
                 s_x_walls[i].vx *= -1;
        } else {
            /* left edge collison */
            if (get_screen_cache(
                    &g_cache,
                    s_x_walls[i].x + s_x_walls[i].vx, s_x_walls[i].y)
                    == '+')
                 s_x_walls[i].vx *= -1;
        }

        /* draw */
        set_screen_cache(
            &g_cache, s_x_walls[i].x, s_x_walls[i].y, s_x_walls[i].str[0]);
        set_screen_cache(
            &g_cache, s_x_walls[i].x + 1, s_x_walls[i].y, s_x_walls[i].str[1]);
        set_screen_cache(
            &g_cache, s_x_walls[i].x + 2, s_x_walls[i].y, s_x_walls[i].str[2]);
    }
    s_first_flag = 0;
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
