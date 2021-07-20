#include <iostream>

// TODO: move this somewhere eventually
struct Vertex {
  float x;
  float y;
  void print() {
    std::cout << "{ x: " << x << ", y: " << y << " }" << std::endl;
  }
};