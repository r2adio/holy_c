#pragma once

#include "raylib.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 8
#define TILE_SIZE 42
#define TILE_TYPES 5

#define SCORE_FONT_SIZE 20

extern char board[BOARD_SIZE][BOARD_SIZE];
extern Vector2 grid_origin;
extern size_t score;

void init_board();
