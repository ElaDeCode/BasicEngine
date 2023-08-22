#include "cuboid.h"
#include "glad/gl.h"
#include <stdlib.h>

static float cuboidVertices[] = {
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

Cuboid *newCuboid() {
  Cuboid *cuboid = malloc(sizeof(Cuboid));

  glGenVertexArrays(1, &cuboid->vao);
  glGenBuffers(1, &cuboid->vbo);
  glGenBuffers(1, &cuboid->ibo);

  transferData(cuboid->vao, cuboid->vbo, cuboid->ibo);

  return cuboid;
}

void transferData(unsigned int vao, unsigned int vbo, unsigned int ibo) {
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cuboidVertices), cuboidVertices,
               GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cuboidIndices), cuboidIndices,
               GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void destroyCuboid(Cuboid *cuboid) {
  glDeleteVertexArrays(1, &cuboid->vao);
  glDeleteBuffers(1, &cuboid->vbo);
  glDeleteBuffers(1, &cuboid->ibo);
  free(cuboid);
}

void drawCuboid(Cuboid *cuboid) {
  glBindVertexArray(cuboid->vao);
  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}