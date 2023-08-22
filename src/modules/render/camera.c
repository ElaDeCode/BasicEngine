#include "camera.h"
#include "engine.h"
#include "glad/gl.h"
#include "math.h"
#include "math/linearAlgebra.h"
#include "math/scaler.h"
#include "modules/io/keyHandle.h"
#include "stdlib.h"

extern Engine engine;

Camera *newCamera() {
  Camera *camera;
  camera = calloc(1, sizeof(Camera));
  // setProjection(camera->projection);
  return camera;
}

void handleCameraMovement(Camera *camera) {
  Window window = engine.window;

  vec3 movementDir;
  movementDir.x = getAxis(window, GLFW_KEY_D, GLFW_KEY_A);
  movementDir.y = getAxis(window, GLFW_KEY_E, GLFW_KEY_Q);
  movementDir.z = getAxis(window, GLFW_KEY_W, GLFW_KEY_S);

  vec3 forward, right, up;
  getRight((float *)&camera->rotation, (float *)&right);
  getUp((float *)&camera->rotation, (float *)&up);
  getForward((float *)&camera->rotation, (float *)&forward);

  scaleArray((float *)&right, movementDir.x, 3);
  scaleArray((float *)&up, movementDir.y, 3);
  scaleArray((float *)&forward, movementDir.z, 3);

  translate((float *)&camera->position, (float *)&right);
  translate((float *)&camera->position, (float *)&up);
  translate((float *)&camera->position, (float *)&forward);

  if (engine.mouseCaptured) {

    int windowSize[2];
    glfwGetWindowSize(window.window, windowSize, windowSize + 1);

    double cursorPos[2];
    glfwGetCursorPos(window.window, cursorPos, cursorPos + 1);

    camera->rotation.yaw += (cursorPos[0] - windowSize[0] / 2.0) / 100;
    camera->rotation.pitch += (windowSize[1] / 2.0 - cursorPos[1]) / 100;

    glfwSetCursorPos(window.window, windowSize[0] / 2.0, windowSize[1] / 2.0);
  }
}

void destroyCamera(Camera *camera) { free(camera); }