#pragma once

#include <GL/glew.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <flecs.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>

#include "shaders/shaders.hpp"

class Engine {
 public:
  Engine(const char* title);
  ~Engine();

  void initSDL(const char* title);  // Add width and height back in later
                                    // with resolution selection
  void initGL();

  void update(float dt);
  void render();

  bool running() { return _running; }

 private:
  SDL_Window* window{nullptr};
  SDL_GLContext context{nullptr};

  flecs::world ecs;

  glm::vec4 vec{glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)};
  glm::mat4 trans{glm::mat4(1.0f)};

  Shader* test{nullptr};

  bool _running{false};
};