#include "engine.h"
#include "modules/io/keys.h"

extern Engine engine;

void updateEngine() {
  engine.deltaTime = glfwGetTime();
  engine.deltaTime -= engine.time;
  engine.time = engine.deltaTime + engine.time;

  double mousePos[2];
  // hide cursor
  engine.mouseCaptured = getMouseButton(engine.window, MOUSE_BUTTON_LEFT);
  // get mouse delta
  getCursorPos(engine.window, mousePos, mousePos + 1);
  engine.mouseDelta[0] = mousePos[0] - engine.mousePos[0];
  engine.mouseDelta[1] = mousePos[1] - engine.mousePos[1];
  engine.mousePos[0] = mousePos[0];
  engine.mousePos[1] = mousePos[1];

  if (engine.mouseCaptured) {
    setInputMode(engine.window, CURSOR, CURSOR_DISABLED);
  } else {
    setInputMode(engine.window, CURSOR, CURSOR_NORMAL);
    getCursorPos(engine.window, engine.mousePos, engine.mousePos + 1);
  }
}