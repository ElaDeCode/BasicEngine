#ifndef CUBOID_H
#define CUBOID_H

#include "transform.h"

typedef struct Cuboid {
  unsigned int vao, vbo, ibo, shader;
  Transform transform;
  int _uPosition; // stores the uniform uPosition adress on the shader
} Cuboid;

void transferData(unsigned int vao, unsigned int vbo, unsigned int ibo);
Cuboid *newCuboid(float xScale, float yScale, float zScale);
void destroyCuboid(Cuboid *cuboid);
void drawCuboid(Cuboid *cuboid);

#endif