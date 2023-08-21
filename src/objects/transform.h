#ifndef TRANSFORM_H
#define TRANSFORM_H

typedef struct Position {
  float x, y, z;
} Position;

typedef struct Rotation {
  float yaw, pitch, roll;
} Rotation;

typedef struct Transform {
  Position position;
  Rotation rotation;
} Transform;

void getRotationMatrix(float yaw, float pitch, float roll, float result[9]);

#endif