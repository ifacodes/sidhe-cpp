#pragma once

#include <GL/glew.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <flecs.h>

#include <iostream>
#include <string>

#include "rendering/map_renderer.hpp"
#include "resources/resource_manager.hpp"
#include "shaders/shaders.hpp"

class Engine {
 public:
  Engine(const char* title) {
    initSDL(title);
    _running = true;
  }
  ~Engine();

  void initSDL(const char* title);  // Add width and height back in later
                                    // with resolution selection
  void init();

  void updateViewport();
  void update(float dt);
  void render();

  bool running() { return _running; }

 private:
  SDL_Window* window{nullptr};
  SDL_GLContext context{nullptr};

  ResourceManager* rm{nullptr};

  int width{0}, height{0};

  flecs::world ecs;
  MapRenderer* mr{nullptr};
  float vertices[4] = {0.0f, 0.0f, 1.0f, 0.0f};

  bool _running{false};
};