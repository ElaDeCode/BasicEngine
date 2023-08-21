#include "camera.h"
#include "glad/gl.h"
#include "math.h"
#include "math/linearAlgebra.h"
#include "stdlib.h"

Camera *newCamera() {
  Camera *camera;
  camera = calloc(1, sizeof(Camera));
  // setProjection(camera->projection);
  return camera;
}

void destroyCamera(Camera *camera) { free(camera); }

// void setProjection(float mat[4][4], float far, float near) {}

// inline void setCameraUniforms(Camera *camera, GLuint shader, const char *pos,
// const char *rot) { camera->uPos = glGetUniformLocation(shader, pos);
// camera->uRot = glGetUniformLocation(shader, rot);
// }