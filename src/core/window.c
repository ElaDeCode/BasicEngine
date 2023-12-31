#include "window.h"
#include "glad/gl.h"

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#include "engine.h"

inline Window createWindow(int width, int height, const char *title) {
  Window window;
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_RESIZABLE, 0);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  window = glfwCreateWindow(width, height, title, 0, 0);
  if (window == NULL) {
    glfwTerminate();
    printf("failed to initialize window\n");
    exit(1);
  }
  glfwSetWindowAttrib(window, GLFW_RESIZABLE, 1);
  glfwMakeContextCurrent(window);

  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

  return window;
}

inline void destroyWindow(Window window) { glfwDestroyWindow(window); }

void framebufferSizeCallback(Window window, int width, int height) {
  glViewport(0, 0, width, height);
  extern Engine engine;
  engine.windowSize[0] = width;
  engine.windowSize[1] = height;
}

inline void getWindowSize(Window window, int *width, int *height) {
  glfwGetWindowSize(window, width, height);
}

inline void setWindowSize(Window window, int width, int height) {
  glfwSetWindowSize(window, width, height);
}

inline void setWindowTitle(Window window, const char *title) {
  glfwSetWindowTitle(window, title);
}

inline void setInputMode(Window window, int mode, int value) {
  glfwSetInputMode(window, mode, value);
}

inline int windowShouldClose(Window window) {
  return glfwWindowShouldClose(window);
}

inline void pollEvents() { glfwPollEvents(); }

inline void swapBuffers(Window window) { glfwSwapBuffers(window); }

inline void getCursorPos(Window window, double *x, double *y) {
  glfwGetCursorPos(window, x, y);
}

inline void setCursorPos(Window window, double x, double y) {
  glfwSetCursorPos(window, x, y);
}

inline int getMouseButton(Window window, int button) {
  glfwGetMouseButton(window, button);
}

inline void swapInterwal(int interval) { glfwSwapInterval(interval); }