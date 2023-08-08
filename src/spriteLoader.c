#include "spriteLoader.h"
#include "edc/edc_sprite.h"
#include "edc/edc_vec.h"
#include "glad/gl.h"
#include <GL/gl.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

static unsigned int drawOrder[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

int loadSprite(const char *path, Sprite *sprite, int frameCount) {
  int nrChannels;
  float frameW, frameH;

  sprite->frameCount = frameCount;

  sprite->data =
      stbi_load(path, &sprite->width, &sprite->height, &nrChannels, 0);

  if (sprite->data == NULL) {
    return 0;
  }

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sprite->width, sprite->height, 0,
               GL_RGBA, GL_UNSIGNED_BYTE, sprite->data);

  frameW = (float)sprite->width / (float)frameCount;
  frameH = (float)sprite->height;

  sprite->vertexAttributes = (EDCquadVertexAttributes){
      {frameW / 2, frameH / 2, 1.0 / frameCount, 1},  // top right
      {frameW / 2, -frameH / 2, 1.0 / frameCount, 0}, // bottom right
      {-frameW / 2, -frameH / 2, 0, 0},               // bottom left
      {-frameW / 2, frameH / 2, 0, 1}                 // top left
  };

  stbi_image_free(sprite->data);

  sprite->indices = drawOrder;

  glBufferData(GL_ARRAY_BUFFER, sizeof(sprite->vertexAttributes),
               &sprite->vertexAttributes, GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int),
               sprite->indices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
                        (void *)(2 * sizeof(float)));
  glEnableVertexAttribArray(1);

  return 1;
}