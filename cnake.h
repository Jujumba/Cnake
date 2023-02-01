#ifndef C_CNAKE_H
#define C_CNAKE_H

#include "conio.h"
#include "stdlib.h"
#include "stdio.h"
#include <time.h>
#include "string.h"
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

void start_game();

#endif //C_CNAKE_H
