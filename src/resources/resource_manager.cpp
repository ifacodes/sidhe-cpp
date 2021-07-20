#include "resource_manager.hpp"

ResourceManager::ResourceManager() {}

ResourceManager::~ResourceManager() {}

std::shared_ptr<Texture> ResourceManager::getTexture(
    std::string_view texture_name) {
  // TODO: this will be replace by fetching the correct filepath from a
  // File Resource

  if (!resources.contains(texture_name.data())) {
    std::shared_ptr<Resource> rp = std::make_shared<Texture>(texture_name);
    resources.insert({texture_name.data(), rp});
  }

  return std::dynamic_pointer_cast<Texture>(resources[texture_name.data()]);
}