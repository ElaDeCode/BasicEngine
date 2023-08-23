#ifndef CUBOID_H
#define CUBOID_H

#include "transform.h"

typedef struct Cuboid {
  Position position;
  Rotation rotation;
  Scale scale;
  // address of the variabless which are stored in gpu
  unsigned int shader; // adress of the shader
  int _uPosition; // visual position
  int _uRotation; // visual rotation
  int _uScale; // visual scale
} Cuboid;

void initCuboid();
void terminateCuboid();
void drawCuboid();
void drawCuboidsInstanced(unsigned int count);

#endif