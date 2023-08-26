#include "camera.h"
#include "engine.h"
#include "glad/gl.h"
#include "math/scaler.h"
#include "modules/io/keyHandle.h"
#include "stdlib.h"

extern Engine engine;

Camera *newCamera() { return calloc(1, sizeof(Camera)); }

inline void handleCameraMovement(Camera *camera) {
  // todo add a function to change movement speed
  float movementSpeed = 0.1;
  float mouseSensivity = 0.01;

  // Get main window
  Window window = engine.window;

  // Get input direction
  vec3 movementDir;
  movementDir[X] = getAxis(window, GLFW_KEY_D, GLFW_KEY_A);
  movementDir[Y] = getAxis(window, GLFW_KEY_E, GLFW_KEY_Q);
  movementDir[Z] = getAxis(window, GLFW_KEY_W, GLFW_KEY_S);

  // Calculate relative directions
  vec3 forward, right, up;
  getRight(camera->rotation, right);
  getUp(camera->rotation, up);
  getForward(camera->rotation, forward);
  // getRelativeAxis((float*)camera->rotation,(float*)&right,(float*)&up,(float*)&forward);

  // Scale relative directions with movementSpeed
  scaleArray(right, movementDir[X] * movementSpeed, 3);
  scaleArray(up, movementDir[Y] * movementSpeed, 3);
  scaleArray(forward, movementDir[Z] * movementSpeed, 3);

  // Move camera on relative directions with movementSpeed
  translate(camera->position, right);
  translate(camera->position, up);
  translate(camera->position, forward);

  // Handle captured mouse movement
  if (engine.mouseCaptured) {
    int windowSize[2];
    glfwGetWindowSize(window, windowSize, windowSize + 1);

    double cursorPos[2];
    glfwGetCursorPos(window, cursorPos, cursorPos + 1);

    // Adjust camera rotation based on mouse movement
    camera->rotation[YAW] +=
        (cursorPos[X] - windowSize[X] / 2.0) * mouseSensivity;
    camera->rotation[PITCH] +=
        (windowSize[Y] / 2.0 - cursorPos[Y]) * mouseSensivity;
  }

  // Calcute rotation matrix for shader
  float rotation[9];
  getRotationMatrix(camera->rotation[PITCH], camera->rotation[YAW], camera->rotation[ROLL], rotation);

  // Pass rotation matrix to shader
  glUniformMatrix3fv(camera->uRot, 1, GL_FALSE, rotation);

  // Pass position to shader
  glUniform3f(             //
      camera->uPos,        //
      camera->position[X], //
      camera->position[Y], //
      camera->position[Z]  //
  );
}

inline void bindCamera(unsigned int shader, Camera *camera) {
  camera->uPos = glGetUniformLocation(shader, "uCameraPosition");
  camera->uRot = glGetUniformLocation(shader, "uCameraRotation");
}

inline void destroyCamera(Camera *camera) { free(camera); }