#pragma once

#include <memory>
#include <string>
#include <unordered_map>

class Resource {
  virtual void load() = 0;
  virtual ~Resource(){};
};

class ResourceManager {
 public:
  ResourceManager();
  ~ResourceManager();

 private:
  std::unordered_map<std::string, std::shared_ptr<Resource>> resources{};
};