#include "main.h"

const char tile_chars[TILE_TYPES] = {'#', '@', '$', '%', '&'};

char board[BOARD_SIZE][BOARD_SIZE] = {0};

// returns a random ith value from tile_chars[]
char random_tile() { return tile_chars[rand() % TILE_TYPES]; }

// populates the matrix with random tile_chars values
void init_board() {
  for (int y = 0; y < BOARD_SIZE; y++) {
    for (int x = 0; x < BOARD_SIZE; x++) {
      board[y][x] = random_tile();
    }
  }
}
