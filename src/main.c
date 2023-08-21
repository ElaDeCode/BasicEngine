#include "engine.h"
#include "modules/io/window.h"
#include "modules/sceneManager.h"

#include <stdio.h>
#include <stdlib.h>

#define WIDTH 800
#define HEIGHT 600
#define TITLE "best title ever"

Engine engine;

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
  engine.isRunning = 1;
  engine.mouseCaptured = 1;
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
  }
  glViewport(0, 0, WIDTH, HEIGHT);
}