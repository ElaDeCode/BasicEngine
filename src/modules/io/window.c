#include "window.h"
#include "glad/gl.h"

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

inline Window createWindow(int width, int height, const char *title) {
  Window window;
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_RESIZABLE, 0);
  window = glfwCreateWindow(width, height, title, 0, 0);
  if (window == NULL) {
    glfwTerminate();
    printf("failed to initialize window\n");
    exit(1);
  }
  glfwSetWindowAttrib(window, GLFW_RESIZABLE, 1);
  glfwMakeContextCurrent(window);
  return window;
}

inline void destroyWindow(Window window) {
  glfwDestroyWindow(window);
}