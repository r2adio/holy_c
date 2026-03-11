#include "raylib.h"
#include <math.h>

#define COLOR RAYWHITE
#define WIN_WIDTH 800
#define WIN_HEIGHT 450
#define SIZE_SCALE (WIN_HEIGHT * 0.1)

void fractal_tree(float x, float y, int size, float width, float angle) {
  if (size < 1)
    return;
  Vector2 start = {x, y};
  Vector2 end = {x + cosf(angle) * size * SIZE_SCALE,
                 y + sinf(angle) * size * SIZE_SCALE};
  DrawLineEx(start, end, width, COLOR);
}

int main(void) {
  InitWindow(WIN_WIDTH, WIN_HEIGHT, "Fractal Tree");
  SetTargetFPS(3);
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    fractal_tree(WIN_WIDTH * 0.5, WIN_HEIGHT - 50, 5, 10, -90 * DEG2RAD);
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
