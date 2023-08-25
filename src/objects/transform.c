#include "transform.h"
#include "math/matrix.h"
#include <math.h>

void getRotationMatrix(float yaw, float pitch, float roll, float result[9]) {
  float tempCos = cosf(yaw);
  float tempSin = sinf(yaw);
  float y[9] = {
      tempCos, 0, -tempSin, //
      0,       1, 0,        //
      tempSin, 0, tempCos   //
  };

  tempCos = cosf(pitch);
  tempSin = sinf(pitch);
  float x[9] = {
      1, 0,       0,        //
      0, tempCos, -tempSin, //
      0, tempSin, tempCos   //
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

inline void getForward(float rotation[3], float forward[3]) {
  forward[0] = cosf(rotation[1]) * sinf(rotation[0]);
  forward[1] = sinf(rotation[1]);
  forward[2] = cosf(rotation[1]) * cosf(rotation[0]);
}

inline void getRight(float rotation[3], float right[3]) {
  right[0] = cosf(rotation[0]);
  right[1] = 0;
  right[2] = -sinf(rotation[0]);
}

inline void getUp(float rotation[3], float up[3]) {
  up[0] = -sinf(rotation[1]) * sinf(rotation[0]);
  up[1] = cosf(rotation[1]);
  up[2] = -sin(rotation[1]) * cosf(rotation[0]);
}

inline void translate(float position[3], float vector[3]) {
  for (int i = 0; i < 3; i++) {
    position[i] += vector[i];
  }
}