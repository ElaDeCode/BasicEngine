#include "core/engine.h"
#include "core/window.h"
#include "scene/sceneManager.h"

#include <stdio.h>
#include <stdlib.h>

#define WIDTH 800
#define HEIGHT 600
#define TITLE "best title ever"

Engine engine = {
    .isRunning = 1,
    .mouseCaptured = 0,
};

//! reminder to move this to the resourceManager.c
void cleanAllResources();

int main() {
  initEngine();

  loadDefaultScene();

  cleanAllResources();
  return 0;
}

void initEngine() {
  glfwInit();
  engine.window = createWindow(WIDTH, HEIGHT, TITLE);
  getWindowSize(engine.window, engine.windowSize, engine.windowSize + 1);
  initOpenGL();
}

//! and dont forget to move to resourceManager.c
void cleanAllResources() {
  destroyWindow(engine.window);
  glfwTerminate();
}

void initOpenGL() {
  int version = gladLoaderLoadGL();
  if (version == 0) {
    printf("error: cannot load opengl\n");
    exit(1);
  }
  glViewport(0, 0, WIDTH, HEIGHT);
}