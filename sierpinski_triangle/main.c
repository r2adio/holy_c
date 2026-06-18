#include <math.h>
#include <raylib.h>

#define WIDTH 900
#define HEIGHT 600

#define SIDE_LEN 300.0

void draw_triangle(Vector2 tip, float side_len) {
  float y = tip.y + side_len * sinf(60 * DEG2RAD);
  Vector2 base_L = {tip.x - side_len / 2, y};
  Vector2 base_R = {tip.x + side_len / 2, y};
  DrawTriangle(tip, base_L, base_R, WHITE);
}

int main(void) {
  InitWindow(WIDTH, HEIGHT, "Sierpinski Triangle");
  SetTargetFPS(10);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    // Vector2 v1 = {WIDTH * 0.5, 50};
    // Vector2 v2 = {WIDTH * 0.5 - 50, 100};
    // Vector2 v3 = {WIDTH * 0.5 + 50, 100};
    // DrawTriangle(v1, v2, v3, WHITE);
    draw_triangle((Vector2){WIDTH * 0.5, 100}, SIDE_LEN);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
