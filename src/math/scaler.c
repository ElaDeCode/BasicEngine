#include "scaler.h"

inline void scaleArray(float *values, float scaler, int n) {
  for (register int i = 0; i < n; i++)
    values[i] *= scaler;
}