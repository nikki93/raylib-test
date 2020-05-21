#include <cmath>
#include <cstdio>
#include <cstdlib>

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

#include <raylib.h>

float randFloat() {
  return ((float)rand()) / ((float)RAND_MAX);
}

int main() {
  const auto W = 800, H = 450;

  InitWindow(W, H, "hello, raylib!");

  const auto N = 20000;

  typedef struct MyRect {
    float x, y;
    Color color;
    float speed;
    int w, h;
    float phase;
  } MyRect;

  MyRect rects[N];

  for (auto &rect : rects) {
    rect.x = W * randFloat();
    rect.y = H * randFloat();
    rect.color.r = rand();
    rect.color.g = rand();
    rect.color.b = rand();
    rect.color.a = 255;
    rect.speed = 400 * randFloat();
    rect.w = 120 * randFloat();
    rect.h = 120 * randFloat();
    rect.phase = 2 * PI * randFloat();
  }

  static auto frame = [&] {
    for (auto &rect : rects) {
      rect.x += rect.speed * sin(GetTime() + rect.phase) * GetFrameTime();
    }

    BeginDrawing();
    ClearBackground(BLACK);
    for (auto &rect : rects) {
      DrawRectangle(rect.x, rect.y, rect.w, rect.h, rect.color);
    }
    {
      static char buf[32];
      snprintf(buf, 32, "fps: %d", GetFPS());
      DrawText(buf, 20, 20, 14, WHITE);
    }
    EndDrawing();
  };

  struct MainLoop {
    static auto doFrame() {
      frame();
    }
  };
#if defined(PLATFORM_WEB)
  emscripten_set_main_loop(MainLoop::doFrame, 0, true);
#else
  SetTargetFPS(120);
  while (!WindowShouldClose()) {
    MainLoop::doFrame();
  }
#endif

  CloseWindow();

  return 0;
}