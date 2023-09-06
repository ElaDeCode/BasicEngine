#ifndef WINDOW_H
#define WINDOW_H

#include "glad/gl.h"
#include <GLFW/glfw3.h>

#define CURSOR GLFW_CURSOR
#define CURSOR_NORMAL GLFW_CURSOR_NORMAL
#define CURSOR_HIDDEN GLFW_CURSOR_HIDDEN
#define CURSOR_DISABLED GLFW_CURSOR_DISABLED

typedef GLFWwindow *Window;

Window createWindow(int width, int height, const char *title);
void destroyWindow(Window window);
void framebufferSizeCallback(Window window, int width, int height);
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
void swapInterwal(int interval);

#endif