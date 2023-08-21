#include "transform.h"
#include "math/linearAlgebra.h"
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