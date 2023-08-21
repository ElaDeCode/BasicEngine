#ifndef WINDOW_H
#define WINDOW_H

#include "glad/gl.h"
#include <GLFW/glfw3.h>

typedef struct Window {
  GLFWwindow *window;
} Window;

Window createWindow(int width, int height, const char *title);
void destroyWindow(Window window);
void setWindowSize(Window window, int width, int height);
void getWindowSize(Window window, int *width, int *height);

#endif