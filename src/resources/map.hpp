#pragma once

#include <GL/glew.h>

#include <vector>

#include "resource.hpp"

/* A Map Resource isn't actually the map vertices,
 * those are always going to be 15 x 10 quads.
 * Instead, it contains the UV positions, for each tile.
 * It depends on the Tileset Texture for the current map
 */

struct UV {
  float u;
  float v;
};

struct Map : Resource {
  Map();
  ~Map();
  virtual void print() const {

  };
};