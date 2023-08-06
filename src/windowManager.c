#include "windowManager.h"
#include "glad/gl.h"
#include <GLFW/glfw3.h>

extern unsigned int shaderProgram;

GLFWwindow *createWindow() {
  GLFWwindow *window;
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  glfwWindowHint(GLFW_REFRESH_RATE, 1);
  window = glfwCreateWindow(800, 600, "akil sagligini kaybet", NULL, NULL);
  glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_TRUE);
  glfwMakeContextCurrent(window);
  return window;
}

/* window change calbacks */
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
  glUniform2f(glGetUniformLocation(shaderProgram, "u_resolution"), width, height);
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, 1);
}