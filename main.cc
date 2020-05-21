#include <cmath>

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

#include "fmt/format.h"

#include "raylib.h"


int main() {
  InitWindow(800, 450, "raylib-test");

  static auto frame = [] {
    BeginDrawing();
    ClearBackground(BLACK);
    EndDrawing();
  };

#if defined(PLATFORM_WEB)
  emscripten_set_main_loop(frame, 0, true);
#else
  SetTargetFPS(120);
  while (!WindowShouldClose()) {
    frame();
  }
#endif

  CloseWindow();

  return 0;
}