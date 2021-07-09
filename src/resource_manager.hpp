#pragma once

#include <string>
#include <unordered_map>

class ResourceManager {
 public:
  ResourceManager();
  ~ResourceManager();

 private:
  std::unordered_map<std::string, std::string> resources{};
};