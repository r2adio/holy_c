#include <raylib.h>

#define WIN_WIDTH  900
#define WIN_HEIGHT 600

int main(void) {
  InitWindow(WIN_WIDTH, WIN_HEIGHT, "nbody simulation");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    EndDrawing();
  }
  CloseWindow();
  return 0;
}
