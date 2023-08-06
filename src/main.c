
#define STB_IMAGE_IMPLEMENTATION
#include "EDC/edcvec.h"
#include "glad/gl.h"
#include "shaderManager.h"
#include "stb_image.h"
#include "windowManager.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

// #define DEBUG
#define WIDTH 800
#define HEIGHT 600

vec2 resolution = {WIDTH, HEIGHT};
unsigned int shaderProgram;

void glTest(GLFWwindow *window);
void init(GLFWwindow **window);
GLFWwindow *createWindow();
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void drawQuad();

int main() {
  GLFWwindow *window;
  init(&window);

  glTest(window);

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

void glTest(GLFWwindow *window) {
  unsigned int VBO;
  unsigned int VAO;
  unsigned int EBO;
  unsigned int texture;

  int width, height, nrChannels;
  unsigned char *data;

  float borderColor[] = {1.0f, 1.0f, 0.0f, 1.0f};

  double timer = glfwGetTime();

  stbi_set_flip_vertically_on_load(1);

  glGenBuffers(1, &VBO);
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &EBO);
  glGenTextures(1, &texture);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

  drawQuad();

  glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glBindTexture(GL_TEXTURE_2D, texture);

  data = stbi_load("textures/choko_10x.png", &width, &height, &nrChannels, 0);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);

  createFullShader(&shaderProgram, "shaders/triangleVert.glsl",
                   "shaders/triangleFrag.glsl", NULL);
  glUseProgram(shaderProgram);
  glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 0);

  /* mainloop */
  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (glfwGetKey(window, GLFW_KEY_F5) || (int)(glfwGetTime() - timer) % 5) {
      createFullShader(&shaderProgram, "shaders/triangleVert.glsl",
                       "shaders/triangleFrag.glsl", NULL);
      int width, height;
      glfwGetWindowSize(window, &width, &height);
      glUniform2f(glGetUniformLocation(shaderProgram, "u_resolution"), width,
                  height);
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
    processInput(window);
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);

  glDeleteProgram(shaderProgram);
}

void drawQuad() {

  float vertices[] = {
      0.5,  0.5,  0.0f, 0.5,  0.15, 0.25, 1, 1, // top right
      0.5,  -0.5, 0.0f, 0.9,  0.7,  0.1,  1, 0, // bottom right
      -0.5, -0.5, 0.0f, 0.15, 0.02, 0.2,  0, 0, // bottom left
      -0.5, 0.5,  0.0f, 0.5,  0.3,  0.7,  0, 1, // top left
  };
  unsigned int indices[] = {
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
  };

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);
}

void init(GLFWwindow **window) {
  unsigned int version;
  if (!glfwInit()) {
    printf("!! cant initialize glfw\n");
    exit(1);
  }
  if ((*window = createWindow()) == NULL) {
    printf("!! cant create window\n");
    glfwTerminate();
    exit(1);
  }
  version = gladLoaderLoadGL();
  if (version == 0) {
    fputs("!! Failed to initialize OpenGL context", stdout);
    glfwTerminate();
    exit(1);
  }
  glViewport(0, 0, WIDTH, HEIGHT);
  glfwSetFramebufferSizeCallback(*window, framebuffer_size_callback);

  /* give user opengl feedback */
  printf("OpenGL Version: %d.%d\n", GLAD_VERSION_MAJOR(version),
         GLAD_VERSION_MINOR(version));
}