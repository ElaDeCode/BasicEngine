#include "glad/gl.h"
#include "sceneManager.h"
#include "window.h"
#include <stb/stb_image.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

int initEngine();
void setCallbacks();
void terminateEngine();

int main() {
  // if glfw initialization fails give error and skip everything except
  if (!initEngine()) {
    printf("there is something bad happened while initializing\n"
           "exiting...\n");
  } else { // if glfw doesnt works dont even bother
    setCallbacks();
    sceneManager();
  }
  // terminate
  terminateEngine();
  return 0; // exit success
}

int initEngine() {
  int version;

  if (!glfwInit()) {
    printf("Couldnt initialize glfw3\n");
  }

  // initialize window
  if (!initWindow()) {
    printf("Could not create window\n");
    return 0;
  }

  // initialize glad
  version = gladLoaderLoadGL();
  if (version == 0) {
    fputs("!! Failed to load OpenGL", stdout);
    return 0;
  }

  // create opengl context
  glViewport(0, 0, WIDTH, HEIGHT);
  
  stbi_set_flip_vertically_on_load(1);

  // give opengl info
  printf("OpenGL Version: %d.%d\n", GLAD_VERSION_MAJOR(version),
         GLAD_VERSION_MINOR(version));

  // exit success
  return 1;
}

void setCallbacks() {
  glfwSetFramebufferSizeCallback(getMainWindow(), frameBufferSizeCallback);
}

void terminateEngine() {
  glfwDestroyWindow(getMainWindow());
  glfwTerminate();
}
