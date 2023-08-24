#ifndef WINDOW_H
#define WINDOW_H

#include "glad/gl.h"
#include <GLFW/glfw3.h>

typedef GLFWwindow *Window;

Window createWindow(int width, int height, const char *title);
void destroyWindow(Window window);
void framebuffer_size_callback(Window window, int width, int height);

#endif