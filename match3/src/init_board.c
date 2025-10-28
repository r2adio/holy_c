#include "main.h"

const char tile_chars[TILE_TYPES] = {'#', '@', '$', '%', '&'};

// generates a random tile
char random_tile() { return tile_chars[rand() % TILE_TYPES]; }

// initializes the board with random tiles
void init_board() {
  for (int y = 0; y < BOARD_SIZE; y++) {
    for (int x = 0; x < BOARD_SIZE; x++) {
      board[y][x] = random_tile();
    }
  }
}
