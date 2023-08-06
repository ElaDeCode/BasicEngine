#ifndef _EDC_WINDOW_MANAGER
#define _EDC_WINDOW_MANAGER

#include "glad/gl.h"
#include <GLFW/glfw3.h>

GLFWwindow *createWindow();
void newWindow();
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

#endif