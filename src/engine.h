#ifndef ENGINE_H
#define ENGINE_H

#include "modules/io/window.h"
#include <stdbool.h>

typedef struct {
  bool isRunning;
  bool mouseCaptured;
  Window window;
} Engine;

void initEngine();
void initOpenGL();

#endif