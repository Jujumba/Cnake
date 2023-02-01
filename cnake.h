#ifndef C_CNAKE_H
#define C_CNAKE_H

#include "conio.h"
#include "stdlib.h"
#include "stdio.h"
#include <time.h>

#ifdef _WIN32
#include "windows.h"
#endif

#define WIDTH 75
#define HEIGHT 25
#define MAX (WIDTH * HEIGHT)

#define FRUIT '$'
#define H_BORDER '-'
#define V_BORDER '|'
#define GREEN "\x1b[32m"
#define BLUE  "\x1b[34m"
#define CYAN  "\x1b[36m"
#define RESET "\x1b[0m"

static char border = '#';

typedef struct {
    int x, y, tl;
    int xs[MAX], ys[MAX];
    char head_char;
    } snake_struct;
typedef enum {UP, DOWN, RIGHT, LEFT} direction;

static snake_struct snake;
static direction dir;
static int fruit_x, fruit_y, game_over, score;
static void spawn_fruit();
static void setup();
static void draw();
static void input();
static void logic();
static void clear(int);
void start_game();
#endif //C_CNAKE_H
