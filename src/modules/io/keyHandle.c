#include "keyHandle.h"
#include "window.h"
#include <GLFW/glfw3.h>

void handleInput(Window *window) {}

inline int getKey(Window window, int key) { return glfwGetKey(window.window, key); }

inline float getAxis(Window window, int keyA, int keyB) {
  return getKey(window, keyA) - getKey(window, keyB);
}