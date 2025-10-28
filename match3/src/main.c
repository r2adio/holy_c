#include "main.h"
#include "raylib.h"

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
        Rectangle rect = {x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
        DrawRectangleLinesEx(rect, 1, DARKGRAY);

        DrawTextEx(GetFontDefault(), TextFormat("%c", board[y][x]),
                   (Vector2){rect.x + 12, rect.y + 8}, 20, 1, WHITE);
      }
    }
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
