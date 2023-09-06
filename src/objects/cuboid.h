#ifndef CUBOID_H
#define CUBOID_H

typedef struct Cuboid {
  float position[3];
  float rotation[3];
  float scale[3];
  unsigned int shader;
} Cuboid;

void initCuboid();
void terminateCuboid();
void drawCuboid();
void drawCuboidsInstanced(unsigned int count);

#endif