#include "../include/glad/gl.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 800
#define HEIGHT 600

#define MAX_SHADERS_SIZE 400

typedef GLuint uint32;

int attachShader(uint32 *shaderProgram);
void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mods);
void sendShaders2Buffers(FILE *fptr, const uint32 filesize, uint32 shader);
int openShader(const char *path, uint32 shader);

const char *VERTEX_SHADER_PATH = "shaders/triangleVert.glsl";
const char *FRAGMENT_SHADER_PATH = "shaders/triangleFrag.glsl";

int main() {
  GLFWwindow *window;

  float vertices[] = {
      0.5f,  0.5f,  0.0f, // top right
      0.5f,  -0.5f, 0.0f, // bottom right
      -0.5f, -0.5f, 0.0f, // bottom left
      -0.5f, 0.5f,  0.0f  // top left
  };
  unsigned int indices[] = {
      // note that we start from 0!
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
  };

  int version;
  uint32 EBO;
  uint32 VBO;
  uint32 VAO;
  uint32 shaderProgram;

  fputs("my test of my sanity continues\n", stdout);

  glfwInit();

  printf("creating window\n");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  glfwWindowHint(GLFW_REFRESH_RATE, 1);
  window = glfwCreateWindow(WIDTH, HEIGHT, "akil sagligini kaybet", NULL, NULL);
  glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_TRUE);
  glfwMakeContextCurrent(window);

  glfwSetKeyCallback(window, key_callback);

  if (!gladLoaderLoadGL()) {
    printf("cannot load glad");
    return -1;
  }

  printf("Loading Glad\n");
  version = gladLoaderLoadGL();
  if (version == 0) {
    fputs("Failed to initialize OpenGL context", stdout);
    glfwTerminate();
    return -1;
  }
  printf("OpenGL Version: %d.%d\n", GLAD_VERSION_MAJOR(version),
         GLAD_VERSION_MINOR(version));

  glViewport(0, 0, WIDTH, HEIGHT);

  printf("attaching shader\n");
  if (attachShader(&shaderProgram) == -1) {
    glfwTerminate();
    return -1;
  }

  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    if (glfwGetKey(window, GLFW_KEY_F))
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glClearColor(0.1, 0.1, 0.15, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glfwSwapBuffers(window);
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteProgram(shaderProgram);

  glfwTerminate();
  return 0;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int openShader(const char *path, uint32 shader) {
  GLchar *buffer;
  FILE *fptr;
  int filesize;

  fptr = fopen(path, "r");
  if (fptr == NULL) {
    printf("\t !! unable to open shader file\n");
    return -1;
  }
  printf("calculating filesize\n");
  fseek(fptr, 0, SEEK_END);
  filesize = ftell(fptr) + 1;
  fseek(fptr, 0, SEEK_SET);
  printf("filesize : %d\n", filesize);

  printf("allocating buffer\n");
  buffer = malloc(sizeof(char) * filesize + 1);
  printf("writing shader to buffer\n");
  fread(buffer, sizeof(char), filesize - 1, fptr);
  buffer[filesize] = '\0';

  printf("\nshader:\n%s\n\n", buffer);

  printf("getting shader source" "\n");
  glShaderSource(shader, 1, (const char **)&buffer, &filesize);
  printf("compiling shader\n");
  glCompileShader(shader);

  printf("free buffer\n");
  fclose(fptr);
  return 0;
}

int attachShader(uint32 *shaderProgram) {
  uint32 vertexShader;
  uint32 fragmentShader;

  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  if (openShader(VERTEX_SHADER_PATH, vertexShader) == -1)
    return -1;

  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  if (openShader(FRAGMENT_SHADER_PATH, fragmentShader) == -1)
    return -1;

  *shaderProgram = glCreateProgram();
  glAttachShader(*shaderProgram, vertexShader);
  glAttachShader(*shaderProgram, fragmentShader);

  glLinkProgram(*shaderProgram);
  glUseProgram(*shaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return 0;
}