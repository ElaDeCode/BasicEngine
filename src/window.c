#include "window.h"
#include "glad/gl.h"
#include <GLFW/glfw3.h>

#define WIDTH 800
#define HEIGHT 600
#define TITLE "i feel a bit numb"

static GLFWwindow *window;

int initWindow() {
  // set resizable false to prevent from auto tiling
  // then set it true for rasizable window
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  // ? i dont even know if this works
  glfwWindowHint(GLFW_REFRESH_RATE, 1);
  window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
  if (window == NULL) {
    return 0;
  }
  glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_TRUE);
  glfwMakeContextCurrent(window);
  return 1;
}

void frameBufferSizeCallback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

GLFWwindow *getMainWindow() { return window; }
