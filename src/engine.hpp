#pragma once

#include <GL/glew.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <iostream>
#include <string>

class Engine {
 public:
  Engine(const char* title);
  ~Engine();

  void initSDL(const char* title);  // Add width and height back in later
                                    // with resolution selection
  void initGL();

  void update();
  void render();

  bool running() { return _running; }

 private:
  SDL_Window* window{nullptr};
  SDL_GLContext context{nullptr};

  bool _running{false};
};