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
  float movementSpeed = 0.01;
  float mouseSensivity = 0.01;

  // Get main window
  Window window = engine.window;

  // Get input direction
  vec3 movementDir;
  movementDir.x = getAxis(window, GLFW_KEY_D, GLFW_KEY_A);
  movementDir.y = getAxis(window, GLFW_KEY_E, GLFW_KEY_Q);
  movementDir.z = getAxis(window, GLFW_KEY_W, GLFW_KEY_S);

  // Calculate relative directions
  vec3 forward, right, up;
  getRight((float *)&camera->rotation, (float *)&right);
  getUp((float *)&camera->rotation, (float *)&up);
  getForward((float *)&camera->rotation, (float *)&forward);
  // getRelativeAxis((float*)camera->rotation,(float*)&right,(float*)&up,(float*)&forward);

  // Scale relative directions with movementSpeed
  scaleArray((float *)&right, movementDir.x * movementSpeed, 3);
  scaleArray((float *)&up, movementDir.y * movementSpeed, 3);
  scaleArray((float *)&forward, movementDir.z * movementSpeed, 3);

  // Move camera on relative directions with movementSpeed
  translate((float *)&camera->position, (float *)&right);
  translate((float *)&camera->position, (float *)&up);
  translate((float *)&camera->position, (float *)&forward);

  // Handle captured mouse movement
  if (engine.mouseCaptured) {
    int windowSize[2];
    glfwGetWindowSize(window, windowSize, windowSize + 1);

    double cursorPos[2];
    glfwGetCursorPos(window, cursorPos, cursorPos + 1);

    // Adjust camera rotation based on mouse movement
    camera->rotation.yaw +=
        (cursorPos[0] - windowSize[0] / 2.0) * mouseSensivity;
    camera->rotation.pitch +=
        (windowSize[1] / 2.0 - cursorPos[1]) * mouseSensivity;
  }

  // Calcute rotation matrix for shader
  float rotation[9];
  getRotationMatrix(camera->rotation.yaw, camera->rotation.pitch, camera->rotation.roll, rotation);

  // Pass rotation matrix to shader
  glUniformMatrix3fv(camera->uRot, 1, GL_FALSE, rotation);

  // Pass position to shader
  glUniform3f(            //
      camera->uPos,       //
      camera->position.x, //
      camera->position.y, //
      camera->position.z  //
  );
}

inline void bindCamera(unsigned int shader, Camera *camera) {
  camera->uPos = glGetUniformLocation(shader, "uCameraPosition");
  camera->uRot = glGetUniformLocation(shader, "uCameraRotation");
}

inline void destroyCamera(Camera *camera) { free(camera); }