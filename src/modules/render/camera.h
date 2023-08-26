#ifndef CAMERA_H
#define CAMERA_H

#include "objects/transform.h"

typedef struct Camera {
  vec3 position;
  vec3 rotation;
  int uPos;
  int uRot;
} Camera;

Camera *newCamera();
void handleCameraMovement(Camera *camera);
void bindCamera(unsigned int shader, Camera *camera);
void destroyCamera(Camera *camera);

#endif