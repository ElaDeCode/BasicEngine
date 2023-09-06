// camera.c

#include "camera.h"
#include "engine.h"
#include "glad/gl.h"
#include "modules/io/keyHandle.h"
#include "modules/io/keys.h"
#include "objects/transform.h"

// CGLM_FORCE_LEFT_HANDED is defined
#include <cglm/clipspace/persp_lh_no.h>
#include <stdlib.h>

extern Engine engine;

Camera *newCamera() {
  Camera *camera = (Camera *)malloc(sizeof(Camera));
  Window window = engine.window;

  camera->fov = 45;
  camera->sensivity = 0.005;
  camera->speed = 0.1;

  glm_vec3_copy((vec3){0, 0, 0}, camera->rotation);
  glm_vec3_copy((vec3){0, 0, 3}, camera->position);

  glm_perspective(camera->fov,
                  (float)engine.windowSize[X] / (float)engine.windowSize[Y],
                  0.1, 100, camera->projection);

  glm_mat4_identity(camera->view);

  glm_translate(camera->view, camera->position);

  glm_mat4_mul(camera->projection, camera->view, camera->view);
  return camera;
}

void updateCamera(Camera *camera) {
  handleCameraMovement(camera);
  glUniformMatrix4fv(camera->uProjection, 1, GL_FALSE, (float *)camera->view);
}

void handleCameraMovement(Camera *camera) {
  glm_perspective(camera->fov,
                  (float)engine.windowSize[X] / (float)engine.windowSize[Y],
                  0.1, 100, camera->projection);

  glm_mat4_identity(camera->view);

  if (engine.mouseCaptured) {
    camera->rotation[PITCH] += engine.mouseDelta[1] * camera->sensivity;
    camera->rotation[YAW] += engine.mouseDelta[0] * camera->sensivity;
  }

  glm_rotate(camera->view, camera->rotation[PITCH], (vec3){1, 0, 0});
  glm_rotate(camera->view, camera->rotation[YAW], (vec3){0, 1, 0});
  glm_rotate(camera->view, camera->rotation[ROLL], (vec3){0, 0, 1});

  camera->right[0] = camera->view[0][0];
  camera->right[1] = camera->view[1][0];
  camera->right[2] = camera->view[2][0];

  camera->up[0] = camera->view[0][1];
  camera->up[1] = camera->view[1][1];
  camera->up[2] = camera->view[2][1];

  camera->forward[0] = camera->view[0][2];
  camera->forward[1] = camera->view[1][2];
  camera->forward[2] = camera->view[2][2];

  vec3 movement = {0, 0, 0};
  glm_vec3_muladds(camera->forward,
                   -getAxis(engine.window, KEY_W, KEY_S) * camera->speed,
                   movement);
  glm_vec3_muladds(camera->right,
                   -getAxis(engine.window, KEY_D, KEY_A) * camera->speed,
                   movement);
  glm_vec3_muladds(camera->up,
                   -getAxis(engine.window, KEY_SPACE, KEY_LEFT_SHIFT) *
                       camera->speed,
                   movement);
  // add movement to position
  glm_vec3_add(camera->position, movement, camera->position);

  // move camera
  glm_translate(camera->view, camera->position);
  // merge projection and view matrix
  glm_mat4_mul(camera->projection, camera->view, camera->view);
}

void bindCamera(Camera *camera) {
  camera->uProjection = glGetUniformLocation(camera->shader, "projection");
}

void destroyCamera(Camera *camera) { free(camera); }