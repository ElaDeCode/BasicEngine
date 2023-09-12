// camera.c

#include "camera.h"
#include "core/engine.h"
#include "glad/gl.h"
#include "core/keyHandle.h"
#include "core/inputMap.h"
#include "object/transform.h"

// CGLM_FORCE_LEFT_HANDED is defined
#include <cglm/clipspace/persp_lh_no.h>
#include <stdlib.h>

extern Engine engine;

// constructor
Camera *newCamera() {
  Camera *camera = (Camera *)calloc(1, sizeof(Camera));
  Window window = engine.window;

  camera->fov = 45;
  camera->sensivity = 0.005;
  camera->speed = 0.1;
  camera->far = 1000;
  camera->near = 0.1;

  glm_vec3_copy((vec3){0, 0, 0}, camera->rotation);
  glm_vec3_copy((vec3){0, 0, 0}, camera->position);

  glm_mat4_identity(camera->view);

  glm_translate(camera->view, camera->position);

  updateCamera(camera);
  return camera;
}

void updateCamera(Camera *camera) {
  handleCameraMovement(camera);

  glm_perspective(camera->fov,
                  (float)engine.windowSize[X] / (float)engine.windowSize[Y],
                  camera->near, camera->far, camera->projection);

  // merge projection and view matrix
  glm_mat4_mul(camera->projection, camera->view, camera->camera);

  glUniformMatrix4fv(camera->uProjection, 1, GL_FALSE, (float *)camera->camera);
}

void handleCameraMovement(Camera *camera) {

  // get camera rotation
  if (engine.mouseCaptured) {
    camera->rotation[PITCH] += engine.mouseDelta[1] * camera->sensivity;
    camera->rotation[YAW] += engine.mouseDelta[0] * camera->sensivity;
  }

  // rotate camera around itself
  glm_rotate_at(camera->view, camera->position, camera->rotation[PITCH],
                camera->right);
  glm_rotate_at(camera->view, camera->position, camera->rotation[YAW],
                camera->up);

  camera->rotation[PITCH] = 0;
  camera->rotation[YAW] = 0;

  // get forward, right and up vectors
  camera->right[0] = camera->view[0][0];
  camera->right[1] = camera->view[1][0];
  camera->right[2] = camera->view[2][0];

  camera->up[0] = camera->view[0][1];
  camera->up[1] = camera->view[1][1];
  camera->up[2] = camera->view[2][1];

  camera->forward[0] = camera->view[0][2];
  camera->forward[1] = camera->view[1][2];
  camera->forward[2] = camera->view[2][2];

  // get movement vector
  vec3 movement = {0, 0, 0};
  glm_vec3_muladds(camera->forward,
                   -getAxis(engine.window, KEY_W, KEY_S) * camera->speed,
                   movement);
  glm_vec3_muladds(camera->right,
                   -getAxis(engine.window, KEY_D, KEY_A) * camera->speed,
                   movement);
  glm_vec3_muladds(camera->up,
                   -getAxis(engine.window, KEY_E, KEY_Q) * camera->speed,
                   movement);

  // add movement vector to camera position
  glm_vec3_sub(camera->position, movement, camera->position);

  // move camera
  glm_translate(camera->view, movement);
}

void bindCamera(Camera *camera) {
  camera->uProjection = glGetUniformLocation(camera->shader, "projection");
}

void destroyCamera(Camera *camera) { free(camera); }