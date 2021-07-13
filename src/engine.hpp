#pragma once

#include <GL/glew.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
//#include <flecs.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>

#include "map.hpp"
#include "shaders/shaders.hpp"

class Engine {
 public:
  Engine(const char* title) {
    initSDL(title);
    _running = true;
    map = new Map(15, 10);
  }
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

  int width{0}, height{0};

  // flecs::world ecs;
  Map* map{nullptr};
  float vertices[4] = {0.0f, 0.0f, 1.0f, 0.0f};

  glm::mat4 model =
      glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(120.f, 80.f, 0.0f)),
                 glm::vec3(119.9f, 79.9f, 0.0f));
  glm::mat4 ortho = glm::ortho(0.f, 240.f, 160.f, 0.f, 1.0f, -1.0f);

  Shader* test{nullptr};

  bool _running{false};
};