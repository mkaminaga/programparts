#include <stdio.h>
#include <stdint.h> //uint32_t
#include <stdlib.h> //srand(), rand()
#include <math.h> //pow()
#include <time.h> //time()
#include <unistd.h> //usleep()

#define X_MAX 15
#define Y_MAX 8
#define BALL_NUM 5

/* void clear_screen()
 * clear screen buffer. */
void clear_screen();

/* void draw_screen_cache(uint32_t, uint32_t, uint8_t)
 * set charactor on screen.
 * arg1: x cordinate of the screen
 * arg2: y cordinate of the screen
 * arg3: character set to (x, y)
 * */
void draw_screen_cache(uint32_t x, uint32_t y, char c);

/* void frash_screen()
 * output characters to screen cached in screen buffer. */
void frash_screen();

/* void draw_wall()
 * draw wall. */
void draw_wall();

/* void control_ball(ball_t*)
 * draw ball bounding on wall. */
void control_ball();

/* void control_x_movong_wall(ball_t*)
 * draw moving wall. */
void control_x_movong_wall();

/* wall data */
const char g_wall[Y_MAX][X_MAX] = {
    {' ','+','-','-','-','-','-','-','-','-','-','-','-','-','+'},
    {' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
    {'+','+',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
    {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
    {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','+','+'},
    {'|',' ',' ',' ',' ',' ',' ','+','-','-','-','-','-','+',' '},
    {'+','-','-','-','-','-','-','+',' ',' ',' ',' ',' ',' ',' '}
};

/* buffer */
uint8_t g_screen_buffer[Y_MAX][X_MAX];

int main() {

    for (;;) {
        /* clear buffer */
        clear_screen();

        /* draw static wall */
        draw_wall();

        /* draw x moving wall */
        control_x_movong_wall();

        /* draw ball */
        control_ball();

        /* draw */
        frash_screen();

        /* frash rate */
        usleep(1E5); //0.1sec
    }

    return 0;
}

/* void clear_screen()
 * clear screen buffer. */
void clear_screen() {
    uint32_t x = 0;
    uint32_t y = 0;

    for (y = 0; y < Y_MAX; y++)
        for (x = 0; x < X_MAX; x++)
            g_screen_buffer[y][x] = ' ';
}

/* void draw_screen_cache(uint32_t, uint32_t, uint8_t)
 * set charactor on screen.
 * arg1: x cordinate of the screen
 * arg2: y cordinate of the screen
 * arg3: character set to (x, y)
 * */
void draw_screen_cache(uint32_t x, uint32_t y, char c) {
    if (x > X_MAX) {
        printf("x exceeds limit\n");
        return;
    }
    if (y > Y_MAX){
        printf("y exceeds limit\n");
        return;
    }
    g_screen_buffer[y][x] = c;
}

/* void frash_screen()
 * output characters to screen cached in screen buffer. */
void frash_screen() {
    uint32_t x = 0;
    uint32_t y = 0;

    /* draw all cashe */
    for (y = 0; y < Y_MAX; y++) {
        for (x = 0; x < X_MAX; x++)
            printf("%c", g_screen_buffer[y][x]);
        printf("\n");
    }
    printf("\n");
}

/* void draw_wall()
 * draw wall. */
void draw_wall() {
    uint32_t x = 0;
    uint32_t y = 0;

    /* set wall */
    for (y = 0; y < Y_MAX; y++)
        for (x = 0; x < X_MAX; x++)
            draw_screen_cache(x, y, g_wall[y][x]);
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

    /* set randon seed */
    srand((uint32_t) time(NULL));

    /* initialize s_ball */
    if (s_first_flag == 1) {
        s_ball.x = 6;
        s_ball.y = 4;
        s_ball.vx = pow(-1, rand() % 2);
        s_ball.vy = pow(-1, rand() % 2);
        s_ball.c = '*';
        s_first_flag = 0;
    }

    /* movement */
    s_ball.x += s_ball.vx;
    s_ball.y += s_ball.vy;

    /* collision judgement */
    if (g_screen_buffer[s_ball.y][s_ball.x + s_ball.vx] != ' ') s_ball.vx *= -1;
    if (g_screen_buffer[s_ball.y + s_ball.vy][s_ball.x] != ' ') s_ball.vy *= -1;

    /* draw */
    draw_screen_cache(s_ball.x, s_ball.y, s_ball.c);
}

/* void control_x_movong_wall(ball_t*)
 * draw moving wall. */
void control_x_movong_wall() {
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
        if (g_wall[s_x_wall.y][s_x_wall.x + s_x_wall.vx + 2] != ' ')
             s_x_wall.vx *= -1;
    } else {
        /* left edge collison */
        if (g_wall[s_x_wall.y][s_x_wall.x + s_x_wall.vx] != ' ')
             s_x_wall.vx *= -1;
    }

    /* draw */
    draw_screen_cache(s_x_wall.x, s_x_wall.y, s_x_wall.str[0]);
    draw_screen_cache(s_x_wall.x + 1, s_x_wall.y, s_x_wall.str[1]);
    draw_screen_cache(s_x_wall.x + 2, s_x_wall.y, s_x_wall.str[2]);
}
