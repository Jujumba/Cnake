#include "snake.h"

static void spawn_fruit() {
//    fruit_x = time(0) % (WIDTH - 1) + 1;
//    fruit_y = time(0) % (HEIGHT - 1) + 1;
    fruit_x = rand() % (WIDTH - 1);
    fruit_y = rand() % (HEIGHT - 1);
}

static void setup() {
    snake.head_char = '^';
    for (int i = 0; i < MAX; ++i){
        snake.xs[i] = snake.ys[i] = -1;
    }
    snake.tl = 0;
    score = 0;
    game_over = 0;
    snake.x = rand() % WIDTH;
    snake.y = rand() % HEIGHT;
    spawn_fruit();
}

static void draw() {
    system("cls");

    for (int i = 0; i < WIDTH; ++i) {
        printf("%c", border);
    }

    printf("\tScore: %d\tFruit X: %d, Fruit Y: %d\n", score, fruit_x, fruit_y);
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (j == 0 || j == WIDTH - 1) {
                printf("%c", border);
            } else {
                if (i == snake.y && j == snake.x) {
                    printf("%c", snake.head_char);
                } else if (i == fruit_y && j == fruit_x) {
                    printf("$");
                } else {
                    int print = 0;
                    for (int k = 0; k < snake.tl; ++k) {
                        if (snake.xs[k] == j && snake.ys[k] == i) {
                            printf("o");
                            print = 1;
                        }
                    }
                    if (!print) {
                        printf(" ");
                    }
                }
            }
        }
        printf("\n");
    }

    for (int i = 0; i < WIDTH; ++i) {
        printf("%c", border);
    }
    Sleep(30);
}

static void input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'w':
                dir = UP;
                snake.head_char = '^';
                break;
            case 'a':
                dir = LEFT;
                snake.head_char = '<';
                break;
            case 's':
                dir = DOWN;
                snake.head_char = 'v';
                break;
            case 'd':
                dir = RIGHT;
                snake.head_char = '>';
                break;
        }
    }
}
static void logic() {
    if (snake.tl >= MAX) {
        system("cls");
        printf("You won!");
        game_over = 1;
    }
    int prev_x = snake.xs[0];
    int prev_y = snake.ys[0];
    snake.xs[0] = snake.x;
    snake.ys[0] = snake.y;

    for (int i = 1; i < snake.tl; ++i) {
        int pprev_x = snake.xs[i];
        int pprev_y = snake.ys[i];
        snake.xs[i] = prev_x;
        snake.ys[i] = prev_y;
        prev_x = pprev_x;
        prev_y = pprev_y;
    }
    switch (dir) {
        case LEFT:
            --snake.x;
            break;
        case RIGHT:
            ++snake.x;
            break;
        case UP:
            --snake.y;
            break;
        case DOWN:
            ++snake.y;
            break;
    }
    if (snake.x >= WIDTH || snake.x < 0 || snake.y >= HEIGHT || snake.y < 0) {
        game_over = 1;
    }
    if (snake.x == fruit_x && snake.y == fruit_y) {
        ++snake.tl;
        ++score;
        spawn_fruit();
    }
}
void start_game() {
    setup();
    while (!game_over) {
        draw();
        input();
        logic();
    }
    system("cls");
    printf("Game over.\nYour score: %d\n",score);
}
