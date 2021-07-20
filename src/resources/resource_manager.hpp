#pragma once

#include <any>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include "texture.hpp"

class ResourceManager {
 public:
  ResourceManager();
  ~ResourceManager();

  std::shared_ptr<Texture> getTexture(std::string_view texture_name);

  // will make a new thread perhaps to watch check each file
  // in the map for updates.
  /* void watchFiles(); */

 private:
  std::unordered_map<std::string, std::shared_ptr<Resource>> resources;
};