#include <cmath>

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

#include "fmt/format.h"

#include "raylib.h"
#include "rlgl.h"


int main() {
  InitWindow(800, 450, "raylib-test");

  auto texture = LoadTexture("assets/avatar.png");

  auto x = 100.0f, y = 100.0f;

  static auto update = [&]() {
    auto dt = GetFrameTime();

    if (IsKeyDown(KEY_LEFT)) {
      x -= 400 * dt;
    }
    if (IsKeyDown(KEY_RIGHT)) {
      x += 400 * dt;
    }
    if (IsKeyDown(KEY_UP)) {
      y -= 400 * dt;
    }
    if (IsKeyDown(KEY_DOWN)) {
      y += 400 * dt;
    }
  };

  static auto draw = [&]() {
    ClearBackground(Color { 0xdd, 0xdf, 0xf8, 0xff });

    rlPushMatrix();
    rlTranslatef(x, y, 0);
    DrawTexture(texture, 0, 0, GREEN);
    rlPopMatrix();

    rlPushMatrix();
    rlTranslatef(x + 20, y + 20, 0);
    DrawTexture(texture, 0, 0, RED);
    rlPopMatrix();
  };

  static auto frame = []() {
    update();

    BeginDrawing();
    draw();
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