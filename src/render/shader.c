#include "shader.h"
#include "glad/gl.h"
#include "resource/fileManager.h"
#include <stdio.h>
#include <stdlib.h>

static char infoLog[500];

int createFullShader(unsigned int *shaderProgram, const char *vertPath,
                     const char *fragPath, const char *geoPath) {
  int success;

  glUseProgram(0);
  glDeleteProgram(*shaderProgram);
  *shaderProgram = glCreateProgram();

  /* add shaders */
  if (vertPath != NULL) {
    attachShaderToProgram(*shaderProgram, vertPath, GL_VERTEX_SHADER);
  }
  if (fragPath != NULL) {
    attachShaderToProgram(*shaderProgram, fragPath, GL_FRAGMENT_SHADER);
  }
  if (geoPath != NULL) {
    attachShaderToProgram(*shaderProgram, geoPath, GL_GEOMETRY_SHADER);
  }

  glLinkProgram(*shaderProgram);
  glGetProgramiv(*shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(*shaderProgram, 512, NULL, infoLog);
    printf("shaderProgram LINK_FAILED:\n");
    printf("\t%s\n", infoLog);
  }
  glUseProgram(*shaderProgram);
  return 1;
}

int attachShaderToProgram(unsigned int shaderProgram, const char *path,
                          unsigned int SHADER_TYPE) {
  unsigned int shader;

  shader = glCreateShader(SHADER_TYPE);
  if (compileShader(path, shader) == -1)
    return -1;

  glAttachShader(shaderProgram, shader);
  glDeleteShader(shader);

  return 0;
}

int compileShader(const char *path, unsigned int shader) {
  char *buffer;
  int bufferSize;
  int success;

  bufferSize = createBufferFromFile(&buffer, path);
  if (!buffer) {
    printf("couldn't create buffer\n");
  }

  glShaderSource(shader, 1, (const char **)&buffer, &bufferSize);
  glCompileShader(shader);

  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    printf("shader compilation failed\n"
           "%s\n"
           "at : %s\n",
           infoLog, path);
    return -1;
  }

  free(buffer);
  return 0;
}