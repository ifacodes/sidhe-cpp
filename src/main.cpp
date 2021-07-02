
#include <iostream>

#include "engine.hpp"

int main(int argc, char *args[]) {
  Engine e = Engine("Test Title");

  while (e.running()) {
    e.update();
    e.render();
  }

  return 0;
}