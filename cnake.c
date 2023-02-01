#include "cnake.h"

typedef struct {
    int x, y, tl;
    int xs[MAX], ys[MAX];
    char head_char;
    char body;
    enum {STOP = 0, UP, DOWN, RIGHT, LEFT} direction;
} s_snake;

typedef struct {int x, y} s_fruit;

static s_snake snake;
static int game_over, score;

static s_fruit fruit;

static void clear(int lines) {
    for (int i = 0; i < lines; ++i) {
        printf("\033[F");
    }
}
static void spawn_fruit() {
    int in_snake = 0;
    do {
        fruit.x = rand() % (WIDTH - 1);
        fruit.y = rand() % (HEIGHT - 1);
        for (int i = 0; i < snake.tl; ++i) {
            if (fruit.x == snake.xs[i] && fruit.y == snake.ys[i]) {
                in_snake = 1;
            }
        }
    } while (fruit.x <= 0 || fruit.y <= 0 || in_snake);

}

static void setup() {
    system("cls");
    snake.head_char = '^';
    snake.direction = 1;
    snake.body = BODY;
    snake.tl = 0;
    score = 0;
    game_over = 0;
    snake.x = rand() % WIDTH;
    snake.y = rand() % HEIGHT;
    spawn_fruit();
}

static void draw() {
    clear(WIDTH + 4);
    printf("Press 'x' to quit\n");
    printf("Score: %d\tFruit X: %d, Fruit Y: %d\n", score, fruit.x, fruit.y);
    for (int i = 0; i < WIDTH; ++i) {
        printf("%s%c%s",CYAN, H_BORDER, RESET);
    }
    printf("\n");
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (j == 0 || j == WIDTH - 1) {
                printf("%s%c%s", CYAN, V_BORDER, RESET);
            } else {
                if (i == snake.y && j == snake.x) {
                    printf("%s%c%s",BLUE,snake.head_char, RESET);
                } else if (i == fruit.y && j == fruit.x) {
                    printf("%s%c%s", GREEN, FRUIT, RESET);
                } else {
                    int print = 0;
                    for (int k = 0; k < snake.tl; ++k) {
                        if (snake.xs[k] == j && snake.ys[k] == i) {
                            printf("%c", snake.body);
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
        printf("%s%c%s",CYAN, H_BORDER, RESET);
    }
    Sleep(30);
}

static void input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'w':
                snake.direction = UP;
                snake.head_char = '^';
                break;
            case 'a':
                snake.direction = LEFT;
                snake.head_char = '<';
                break;
            case 's':
                snake.direction = DOWN;
                snake.head_char = 'v';
                break;
            case 'd':
                snake.direction = RIGHT;
                snake.head_char = '>';
                break;
            case 'x':
                snake.direction = STOP;
                break;
            default:
                break;
        }
    }
}
static void logic() {
    if (snake.tl >= MAX) {
        system("cls");
        printf("You won!");
        game_over = 2;
    }
    int prev_x = snake.xs[0];
    int prev_y = snake.ys[0];
    snake.xs[0] = snake.x;
    snake.ys[0] = snake.y;

    for (int i = 1; i < snake.tl; ++i) {
        int curr_x = snake.xs[i];
        int curr_y = snake.ys[i];
        snake.xs[i] = prev_x;
        snake.ys[i] = prev_y;
        prev_x = curr_x;
        prev_y = curr_y;
    }
    switch (snake.direction) {
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
        case STOP:
            game_over = 1;
            break;
    }
    for (int i = 0; i < snake.tl; ++i) {
        if (snake.x == snake.xs[i] && snake.y == snake.ys[i]) {
            game_over = 1;
        }
    }
    if (snake.x >= WIDTH || snake.x < 0 || snake.y >= HEIGHT || snake.y < 0) {
        game_over = 1;
    }
    if (snake.x == fruit.x && snake.y == fruit.y) {
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
    if (game_over == 1) {
        system("cls");
        printf("Game over.\nYour score: %d\n", score);
    }

}
