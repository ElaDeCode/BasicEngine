#ifndef WINDOW_H
#define WINDOW_H

#include "glad/gl.h"
#include <GLFW/glfw3.h>

typedef GLFWwindow *Window;

Window createWindow(int width, int height, const char *title);
void destroyWindow(Window window);
void framebuffer_size_callback(Window window, int width, int height);
void getWindowSize(Window window, int *width, int *height);
void setWindowSize(Window window, int width, int height);
void setWindowTitle(Window window, const char *title);
void setInputMode(Window window, int mode, int value);
int windowShouldClose(Window window);
void pollEvents();
void swapBuffers(Window window);
void getCursorPos(Window window, double *x, double *y);
void setCursorPos(Window window, double x, double y);
int getMouseButton(Window window, int button);

#endif