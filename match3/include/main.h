#pragma once

#include "raylib.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 8
#define TILE_SIZE 42
#define TILE_TYPES 5

extern char board[BOARD_SIZE][BOARD_SIZE];
extern Vector2 grid_origin;

void init_board();
