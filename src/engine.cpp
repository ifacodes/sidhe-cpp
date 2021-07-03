#include "engine.hpp"

Engine::Engine(const char* title) {
  initSDL(title);
  _running = true;
}

Engine::~Engine() {
  SDL_DestroyWindow(window);
  printf("Window Destroyed\n");

  delete test;

  SDL_Quit();
  printf("SDL Quit\n");
}

void Engine::initSDL(const char* title) {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    // printf("Couldn't initialise SDL! SDL_Error: %s\n", SDL_GetError());
    throw std::runtime_error("Couldn't initialise SDL! SDL_Error: " +
                             std::string(SDL_GetError()));
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  window =
      SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                       800, 600, SDL_WINDOW_OPENGL);

  if (!window) {
    throw std::runtime_error("Couldn't create window: " +
                             std::string(SDL_GetError()));
  }

  context = SDL_GL_CreateContext(window);

  if (!context) {
    throw std::runtime_error(
        "OpenGL Context could not be created! SDL Error: " +
        std::string(SDL_GetError()));
  }

  GLenum glewError = glewInit();
  if (glewError != GLEW_OK) {
    throw std::runtime_error("Error Initialising GLEW!");
  }

  if (SDL_GL_SetSwapInterval(-1) < 0) {
    // TODO: Log "Adaptive VSync couldn't be enabled, falling back to VSync"
    if (SDL_GL_SetSwapInterval(1) < 0) {
      throw std::runtime_error("Warning: Unable to set VSync! SDL Error: " +
                               std::string(SDL_GetError()));
    }
  }

  initGL();
}

void Engine::initGL() { test = new Shader("../shaders/test.glsl", true, true); }

void Engine::update(float dt) {
  SDL_Event e;

  while (SDL_PollEvent(&e)) {
    switch (e.type) {
      case SDL_QUIT:
        _running = false;
        break;
    }
  }

  trans = glm::rotate(trans, dt, glm::vec3(0.0f, 0.0f, 1.0f));
  // do update stuff here!
}

void Engine::render() {
  glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  // reset viewport?

  unsigned int transformLoc = glGetUniformLocation(test->ID, "transform");
  test->use();
  glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

  glBindVertexArray(VAO);
  // do rendering here!
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  SDL_GL_SwapWindow(window);
}
