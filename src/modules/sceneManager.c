#include "engine.h"
#include "io/keyHandle.h"
#include "modules/render/shader.h"
#include "objects/cuboid.h"
#include "objects/transform.h"
#include "render/camera.h"
#include "scene.h"

#include "glad/gl.h"
#include <GLFW/glfw3.h>
#include <stdio.h>

extern Engine engine;
Window window;

void loadDefaultScene() {
  window = engine.window;

  unsigned int shader;
  createFullShader(&shader, "assets/shaders/default.vert",
                   "assets/shaders/default.frag", NULL);

  Cuboid *cuboid = newCuboid(0.5, 0.5, 1);
  Camera *camera = newCamera();

  camera->uPos = glGetUniformLocation(shader, "uCameraPos");
  camera->uRot = glGetUniformLocation(shader, "uCameraRot");

  glEnable(GL_DEPTH_TEST);
  while (!glfwWindowShouldClose(engine.window.window)) {
    glClearColor(0.1, 0.15, 0.2, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shader);
    drawCuboid(cuboid);

    if (getKey(window, GLFW_KEY_F)) {
      engine.mouseCaptured = 1;
    } else
      engine.mouseCaptured = 0;

    handleCameraMovement(camera);

    float rotation[9];
    getRotationMatrix(camera->rotation.yaw, camera->rotation.pitch,
                      camera->rotation.roll, rotation);

    glUniformMatrix3fv(camera->uRot, 1, GL_FALSE, rotation);

    glUniform3f(                  //
        camera->uPos,             //
        camera->position.x / 100, //
        camera->position.y / 100, //
        camera->position.z / 100  //
    );

    glfwSwapBuffers(window.window);

    glfwPollEvents();
  }

  destroyCuboid(cuboid);
  destroyCamera(camera);

  glUseProgram(0);
  glDeleteProgram(shader);
}