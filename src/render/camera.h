#ifndef CAMERA_H
#define CAMERA_H

#include <cglm/cglm.h>

typedef struct Camera {

  float fov;
  float sensivity;
  float speed;
  float far;
  float near;
  vec3 rotation;
  vec3 position;

  vec3 right;
  vec3 up;
  vec3 forward;

  mat4 projection;
  mat4 view;
  mat4 camera;

  unsigned int shader;
  int uProjection;

} Camera;

Camera *newCamera();
void handleCameraMovement(Camera *camera);
void updateCamera(Camera *camera);
void bindCamera(Camera *camera);
void destroyCamera(Camera *camera);

#endif // CAMERA_H