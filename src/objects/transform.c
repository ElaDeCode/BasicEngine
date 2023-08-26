#include "transform.h"
#include "math/matrix.h"
#include <math.h>

void getRotationMatrix(float pitch, float yaw, float roll, float result[9]) {

  float tempCos = cosf(pitch);
  float tempSin = sinf(pitch);
  float x[9] = {
      1, 0,       0,        //
      0, tempCos, -tempSin, //
      0, tempSin, tempCos   //
  };

  tempCos = cosf(yaw);
  tempSin = sinf(yaw);
  float y[9] = {
      tempCos, 0, -tempSin, //
      0,       1, 0,        //
      tempSin, 0, tempCos   //
  };

  float midResult[9];
  mat3Mult(x, y, midResult);

  tempCos = cosf(roll);
  tempSin = sinf(roll);
  float z[9] = {
      tempCos, -tempSin, 0, //
      tempSin, tempCos,  0, //
      0,       0,        1  //
  };

  mat3Mult(midResult, z, result);
}

inline void getForward(vec3 rotation, vec3 forward) {
  forward[X] = cosf(rotation[PITCH]) * sinf(rotation[YAW]);
  forward[Y] = sinf(rotation[PITCH]);
  forward[Z] = cosf(rotation[PITCH]) * cosf(rotation[YAW]);
}

inline void getRight(vec3 rotation, vec3 right) {
  right[0] = cosf(rotation[YAW]);
  right[1] = 0;
  right[2] = -sinf(rotation[YAW]);
}

inline void getUp(vec3 rotation, vec3 up) {
  up[0] = -sinf(rotation[PITCH]) * sinf(rotation[YAW]);
  up[1] = cosf(rotation[PITCH]);
  up[2] = -sin(rotation[PITCH]) * cosf(rotation[YAW]);
}

inline void translate(vec3 position, vec3 vector) {
  for (int i = 0; i < 3; i++) {
    position[i] += vector[i];
  }
}