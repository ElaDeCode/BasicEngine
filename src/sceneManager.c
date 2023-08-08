#include "sceneManager.h"
#include "edc/edc_sprite.h"
#include "glad/gl.h"
#include "shaderManager.h"
#include "spriteLoader.h"
#include <GLFW/glfw3.h>

int sceneNotAvailable = 1;
char scenePath[500] = {'\0'};

extern GLFWwindow *getMainWindow();

void sceneManager() {
  if (*scenePath == '\0' || sceneNotAvailable) {
    loadDefaultScene();
  }
  if (!getScene()) {
    // todo handle error
  }
  if (!preProcessScene()) {
    // todo handle error
  }
  if (!loadScene()) {
    // todo handle error
  }
}

int loadDefaultScene() {
  unsigned int shaderProgram;

  unsigned int VBO;
  unsigned int VAO;
  unsigned int EBO;
  unsigned int texture;

  Sprite skelton;

  int u_frameNumber = 0, u_frameWidth;
  unsigned int frameNumber = 0;
  double timer = glfwGetTime();
  GLFWwindow *window = getMainWindow();

  glGenBuffers(1, &VBO);
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &EBO);
  glGenTextures(1, &texture);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBindTexture(GL_TEXTURE_2D, texture);

  // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR,
                  //  (GLfloat[]){1, 1, 1, 1});
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

  loadSprite("assets/textures/skeleton-1_spriteSheet.png", &skelton, 4);

  createFullShader(&shaderProgram, "assets/shaders/triangle.vert",
                   "assets/shaders/triangle.frag", NULL);
  glUseProgram(shaderProgram);
  glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 0);
  glUniform2f(glGetUniformLocation(shaderProgram, "u_resolution"), 800, 600);

  u_frameWidth = glGetUniformLocation(shaderProgram, "u_frameWidth");
  u_frameNumber = glGetUniformLocation(shaderProgram, "u_frameNumber");
  glUniform1f(u_frameWidth, 1.0 / (float)skelton.frameCount);

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (glfwGetKey(window, GLFW_KEY_F5)) {
      createFullShader(&shaderProgram, "assets/shaders/triangle.vert",
                       "assets/shaders/triangle.frag", NULL);
      int width, height;
      glfwGetWindowSize(window, &width, &height);
      glUniform2f(glGetUniformLocation(shaderProgram, "u_resolution"), width,
                  height);
    }

    if ((glfwGetTime() - timer) > .1) {
      timer = glfwGetTime();
      frameNumber = (frameNumber + 1) % skelton.frameCount;
      glUniform1i(u_frameNumber, frameNumber);
    }

    glActiveTexture(GL_TEXTURE);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteTextures(1, &texture);

  return 1;
}

int getScene() {
  /**
   * todo.
   * read files to get scene info
   * get shaders
   * get object positions
   * get textures
   * create buffers
   *? dont delete the buffers
   *? pass address to the resourse manager for easy cleanup
   *! check existence first
   *! add a default to each in case one fails
   */
  return 1;
}

int preProcessScene() {
  /**
   * todo
   */
  return 1;
}

int loadScene() {
  /**
   *
   */
  return 1;
}