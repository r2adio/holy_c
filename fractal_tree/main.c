#include "raylib.h"

void fractal_tree(float x, float y, int width) { DrawPixel(x, y, RAYWHITE); }

int main(void) {
  InitWindow(800, 450, "Fractal Tree");
  SetTargetFPS(3);
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    fractal_tree(100, 200, 10);
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
