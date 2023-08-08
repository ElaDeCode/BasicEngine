#ifndef _EDC_SPRITE
#define _EDC_SPRITE

#include "edc_vec.h"

typedef struct {
  EDCvec2 vertex, texture;
} EDCvertexAttribute2D;

typedef struct {
  EDCvertexAttribute2D topRight, bottomRight, bottomLeft, topLeft;
} EDCquadVertexAttributes;

typedef struct {
  EDCquadVertexAttributes vertexAttributes;
  unsigned int frameCount;
  int width, height;
  unsigned int *indices;
  unsigned char *data;
} Sprite;

#endif