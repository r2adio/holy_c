#include <math.h>
#include <raylib.h>
#include <stddef.h>
#include <stdlib.h>

#define WIDTH 900
#define HEIGHT 600
#define BOB_RAD 15

void draw(size_t len, Vector2 start, float_t theta) {
  DrawLineEx((Vector2){100.0f, 40.0f}, (Vector2){800.0f, 40.0f}, 5.0f, WHITE);
  Vector2 end =
      (Vector2){start.x + len * sinf(theta), start.y + len * cosf(theta)};
  DrawLineEx(start, end, 3, WHITE);
  DrawCircleV(end, BOB_RAD, GRAY);
}

int main(void) {
  InitWindow(WIDTH, HEIGHT, "double pendulum");
  SetTargetFPS(60);
  Vector2 start_pos = (Vector2){WIDTH * 0.5, 40};
  while (!WindowShouldClose()) {
    BeginDrawing();
    draw(200, start_pos, 0 * DEG2RAD);
    EndDrawing();
  }
  return EXIT_SUCCESS;
}
