#include "linearAlgebra.h"

void mat3Mult(float a[9], float b[9], float result[9]) {
  register int i, j, k, tmp;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      result[3 * i + j] = 0;
      for (k = 0; k < 3; k++) {
        result[3 * i + j] += a[3 * i + k] * b[3 * k + j];
      }
    }
  }
}