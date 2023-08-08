#ifndef _EDC_WINDOW_H
#define _EDC_WINDOW_H

#include "glad/gl.h"
#include <GLFW/glfw3.h>

#define WIDTH 800
#define HEIGHT 600
#define TITLE "i feel a bit numb"

int initWindow();
void frameBufferSizeCallback(GLFWwindow *window, int width, int height);
GLFWwindow *getMainWindow();

#endif