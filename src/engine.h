#ifndef ENGINE_H
#define ENGINE_H

#include "modules/io/window.h"
#include <stdbool.h>

typedef struct {
  bool isRunning;
  bool mouseCaptured;
  Window window;
  double time;
  float deltaTime;
  int windowSize[2];
  double mousePos[2];
  double mouseDelta[2];
} Engine;

void initEngine();
void initOpenGL();
void updateEngine();

#endif