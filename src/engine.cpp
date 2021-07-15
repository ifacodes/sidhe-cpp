#include "engine.hpp"

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

  window = SDL_CreateWindow(
      title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 960, 640,
      SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE);

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

void Engine::initGL() {
  test = new Shader("..\\shaders\\test.glsl", true, true);
  SDL_GL_GetDrawableSize(window, &width, &height);
  int ratioX = width / 240.f;
  int ratioY = width / 160.f;
  int ratio = ratioX < ratioY ? ratioX : ratioY;
  int viewW = 240.f * ratio;
  int viewH = 160.f * ratio;
  int viewX = (width - 240.f * ratio) / 2;
  int viewY = (height - 160.f * ratio) / 2;

  glViewport(viewX, viewY, viewW, viewH);
  glScissor(viewX, viewY, viewW, viewH);
}

void Engine::update(float dt) {
  SDL_Event e;

  while (SDL_PollEvent(&e)) {
    switch (e.type) {
      case SDL_QUIT:
        _running = false;
        break;
      case SDL_WINDOWEVENT:
        if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
          updateViewport();
        }
    }
  }
}

void Engine::updateViewport() {
  SDL_GL_GetDrawableSize(window, &width, &height);
  int ratioX = width / 240.f;
  int ratioY = height / 160.f;
  int ratio = ratioX < ratioY ? ratioX : ratioY;
  int viewW = 240.f * ratio;
  int viewH = 160.f * ratio;
  int viewX = (width - 240.f * ratio) / 2;
  int viewY = (height - 160.f * ratio) / 2;

  glViewport(viewX, viewY, viewW, viewH);
  glScissor(viewX, viewY, viewW, viewH);
}

// trans = glm::rotate(trans, dt, glm::vec3(0.0f, 0.0f, 1.0f));
// do update stuff here!

void Engine::render() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
  glEnable(GL_SCISSOR_TEST);
  glClear(GL_COLOR_BUFFER_BIT);
  glDisable(GL_SCISSOR_TEST);

  test->use();

  unsigned int modelLoc = glGetUniformLocation(test->ID, "model");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
  unsigned int orthoLoc = glGetUniformLocation(test->ID, "ortho");
  glUniformMatrix4fv(orthoLoc, 1, GL_FALSE, glm::value_ptr(ortho));

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  map->render();

  // do rendering here!
  glBindVertexArray(0);

  SDL_GL_SwapWindow(window);
}
