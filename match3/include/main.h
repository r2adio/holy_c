#ifndef MAIN_H
#define MAIN_H

#include "raylib.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 8
#define TILE_SIZE 42
#define TILE_TYPES 5

char board[BOARD_SIZE][BOARD_SIZE];

void init_board();

#endif // !MAIN_H
