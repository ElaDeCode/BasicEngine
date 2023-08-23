#ifndef TRANSFORM_H
#define TRANSFORM_H

typedef struct vec3 {
  float x, y, z;
} vec3;

typedef vec3 Position;
typedef vec3 Scale;

typedef struct Rotation {
  float yaw, pitch, roll;
} Rotation;

void getRotationMatrix(float yaw, float pitch, float roll, float result[9]);

void getForward(float rotation[3], float direction[3]);
void getRight(float rotation[3], float right[3]);
void getUp(float rotation[3], float up[3]);

void translate(float position[3], float vector[3]);

#endif