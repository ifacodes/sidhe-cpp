#pragma once
#include "../utils/stb_image.h"
#include "../utils/type_probing.hpp"
#include "resource.hpp"

struct Texture : Resource {
  Texture(std::string_view filename) {
    data = stbi_load(filename.data(), &x, &y, &n, 0);
  };

  virtual void print() const override {
    std::cout << type_name<Texture>() << std::endl;
  };

  int x{0}, y{0}, n{0};
  unsigned char* data{nullptr};
};