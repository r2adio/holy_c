#include "raylib.h"
#include <math.h>

#define COLOR RAYWHITE
#define WIN_WIDTH 1280
#define WIN_HEIGHT 720
#define SIZE_SCALE (WIN_HEIGHT * 0.05)
#define ANGLE_VARIANCE 0.8

void fractal_tree(float x, float y, float size, float width, float angle,
                  int depth) {
  if (depth < 0)
    return;

  Vector2 start = {x, y};
  Vector2 end = {x + cosf(angle) * size * SIZE_SCALE,
                 y + sinf(angle) * size * SIZE_SCALE};
  DrawLineEx(start, end, width, COLOR);
  depth--;

  fractal_tree(end.x, end.y, size - 0.70, width * 0.7, angle - ANGLE_VARIANCE,
               depth);
  fractal_tree(end.x, end.y, size - 0.70, width * 0.7, angle + ANGLE_VARIANCE,
               depth);
}

int main(void) {
  InitWindow(WIN_WIDTH, WIN_HEIGHT, "Fractal Tree");
  SetTargetFPS(3);
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    fractal_tree(WIN_WIDTH * 0.5, WIN_HEIGHT - 10, 5, 10, -90 * DEG2RAD, 40);
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
