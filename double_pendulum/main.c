#include <math.h>
#include <raylib.h>
#include <stddef.h>
#include <stdlib.h>

#define WIDTH 900
#define HEIGHT 600

#define L1 250
#define L2 200
#define BAR_HEIGHT 40.0f
#define BAR_WIDTH 800.0f
#define BOB_RAD 15

void drawBase(Vector2 s) {
  const float deg = 135.0f * DEG2RAD;
  const float len = 40.0f;
  const float baseStartX = 100.0f;
  const float baseEndX = BAR_WIDTH;
  const float spacing = 28.0f;

  for (float x = baseStartX + spacing; x < baseEndX; x += spacing) {
    Vector2 top = (Vector2){x, BAR_HEIGHT};
    Vector2 end = (Vector2){top.x + len * sinf(deg), top.y + len * cosf(deg)};
    DrawLineEx(end, top, 3.0f, GRAY);
  }
  DrawLineEx((Vector2){baseStartX, BAR_HEIGHT}, (Vector2){baseEndX, BAR_HEIGHT},
             5.0f, WHITE);
  // DrawRectangleLinesEx((Rectangle){1, 2, 3, 4}, 5.0f, WHITE);
}

void drawPendulum(size_t len, Vector2 start, float_t theta) {
  drawBase(start);
  Vector2 end =
      (Vector2){start.x + len * sinf(theta), start.y + len * cosf(theta)};
  DrawLineEx(start, end, 3, WHITE);
  DrawCircleV(end, BOB_RAD, GRAY);
}

int main(void) {
  InitWindow(WIDTH, HEIGHT, "double pendulum");
  SetTargetFPS(60);
  Vector2 start_pos = (Vector2){WIDTH * 0.5, BAR_HEIGHT};
  while (!WindowShouldClose()) {
    BeginDrawing();
    drawPendulum(L1, start_pos, 0 * DEG2RAD);
    EndDrawing();
  }
  return EXIT_SUCCESS;
}
