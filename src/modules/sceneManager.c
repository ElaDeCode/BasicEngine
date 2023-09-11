#include "engine.h"
#include "io/keyHandle.h"
#include "io/window.h"
#include "modules/io/keys.h"
#include "modules/render/shader.h"
#include "objects/cuboid.h"
#include "render/camera.h"
#include "scene.h"

#include "glad/gl.h"
#include <stdio.h>

#define DEFAULT_VERT "assets/shaders/cubeFromInstances.vert"
#define DEFAULT_FRAG "assets/shaders/bloom.frag"

extern Engine engine;

void loadDefaultScene() {
  Window window = engine.window;

  unsigned int shader;
  createFullShader(&shader, DEFAULT_VERT, DEFAULT_FRAG, NULL);

  initCuboid();
  Camera *camera = newCamera();
  camera->shader = shader;
  bindCamera(camera);
  updateCamera(camera);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  double lastMeasure = glfwGetTime();
  int fps = 0;

  unsigned int uTime = glGetUniformLocation(shader, "time");
  while (!windowShouldClose(window)) {
    int windowSize[2];
    getWindowSize(window, windowSize, windowSize + 1);

    glUniform1f(uTime, (float)glfwGetTime());

    glClearColor(0.1, 0.15, 0.2, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shader);
    drawCuboidsInstanced(125000);
    // drawCuboid();
    updateCamera(camera);

    swapBuffers(window);

    // calculate fps and reload shader every second
    if (engine.time - lastMeasure > 1) {
      printf("FPS: %d\n", fps);
      lastMeasure = engine.time;
      fps = 0;
      createFullShader(&shader, DEFAULT_VERT, DEFAULT_FRAG, NULL);
      camera->shader = shader;
      updateCamera(camera);
    } else
      ++fps;

    //* poll events
    pollEvents();
    updateEngine();
  }

  terminateCuboid();
  destroyCamera(camera);

  glUseProgram(0);
  glDeleteProgram(shader);
}