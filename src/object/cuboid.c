#include "cuboid.h"
#include "glad/gl.h"

static unsigned int cuboidVAO;
static unsigned int cuboidIBO;

void initCuboid() {

  float cuboidVertices[] = {
      -0.5f, 0.5f,  0.5f,  //
      0.5f,  0.5f,  0.5f,  //
      -0.5f, -0.5f, 0.5f,  //
      0.5f,  -0.5f, 0.5f,  //
      -0.5f, 0.5f,  -0.5f, //
      0.5f,  0.5f,  -0.5f, //
      -0.5f, -0.5f, -0.5f, //
      0.5f,  -0.5f, -0.5f  //
  };

  static unsigned int cuboidIndices[] = {
      4, 5, 1, //
      4, 1, 0, //
      0, 1, 3, //
      0, 3, 2, //
      2, 3, 7, //
      2, 7, 6, //
      6, 7, 5, //
      6, 5, 4, //
      4, 0, 2, //
      4, 2, 6, //
      1, 5, 7, //
      1, 7, 3  //
  };

  unsigned int vbo;

  glGenVertexArrays(1, &cuboidVAO);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &cuboidIBO);

  glBindVertexArray(cuboidVAO);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cuboidVertices), cuboidVertices,
               GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cuboidIBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cuboidIndices), cuboidIndices,
               GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  glDeleteBuffers(1, &vbo);
}

void terminateCuboid() {
  glDeleteBuffers(1, &cuboidIBO);
  glDeleteVertexArrays(1, &cuboidVAO);
}

void drawCuboid() {
  glBindVertexArray(cuboidVAO);
  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

void drawCuboidsInstanced(unsigned int count) {
  glBindVertexArray(cuboidVAO);
  glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, count);
  glBindVertexArray(0);
}