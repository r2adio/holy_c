#include "main.h"
#include "raylib.h"

size_t score = 0;

int main(void) {
  const int screen_width = 800;
  const int screen_height = 450;
  InitWindow(screen_width, screen_height, "ASCII Match");

  SetTargetFPS(60);
  srand(time(NULL));

  init_board();

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    for (int y = 0; y < BOARD_SIZE; y++) {
      for (int x = 0; x < BOARD_SIZE; x++) {
        Rectangle rect = {grid_origin.x + (x * TILE_SIZE),
                          grid_origin.y + (y * TILE_SIZE), TILE_SIZE,
                          TILE_SIZE};
        DrawRectangleLinesEx(rect, 1, DARKGRAY);

        // output the tile character on the board
        DrawTextEx(GetFontDefault(), TextFormat("%c", board[y][x]),
                   (Vector2){rect.x + 12, rect.y + 8}, 20, 1, WHITE);
      }
    }

    DrawText(TextFormat("SCORE: %d", score), 20, 20, 25, ORANGE);

    EndDrawing();
  }
  CloseWindow();
  return 0;
}
