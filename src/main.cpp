
#include <cstdlib>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "engine.hpp"

int main(int argc, char *args[]) {
  Engine e = Engine("Test Title");
  e.init();

  uint64_t prev = SDL_GetPerformanceCounter();
  float acc = 0;

  while (e.running()) {
    uint64_t curr = SDL_GetPerformanceCounter();
    float dt = static_cast<float>(
        (curr - prev) / static_cast<float>(SDL_GetPerformanceFrequency()));
    prev = curr;

    if (abs(dt - (1.0 / 120.0)) < 0.0002) {
      dt = (1.0 / 120.0);
    }
    if (abs(dt - (1.0 / 60.0)) < 0.0002) {
      dt = (1.0 / 60.0);
    }
    if (abs(dt - (1.0 / 30.0)) < 0.0002) {
      dt = (1.0 / 30.0);
    }
    acc += dt;

    while (acc >= (1.0 / 60.0)) {
      e.update(dt);
      acc -= (1.0 / 60.0);
    }
    e.render();
  }

  return 0;
}