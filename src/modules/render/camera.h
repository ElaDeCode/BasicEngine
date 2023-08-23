#ifndef CAMERA_H
#define CAMERA_H

#include "objects/transform.h"

typedef struct Camera {
  Position position;
  Rotation rotation;
  int uPos;
  int uRot;
} Camera;

Camera *newCamera();
void handleCameraMovement(Camera *camera);
void bindCamera(unsigned int shader, Camera *camera);
void destroyCamera(Camera *camera);

#endif