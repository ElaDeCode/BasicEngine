#ifndef TRANSFORM_H
#define TRANSFORM_H

#define X 0
#define Y 1
#define Z 2
#define W 3

#define PITCH 0
#define YAW 1
#define ROLL 2

typedef float vec2[2];
typedef float vec3[3];
typedef float vec4[4];

void getRotationMatrix(float pitch, float yaw, float roll, float result[9]);

void getForward(vec3 rotation, vec3 direction);
void getRight(vec3 rotation, vec3 right);
void getUp(vec3 rotation, vec3 up);

void translate(vec3 position, vec3 vector);

#endif