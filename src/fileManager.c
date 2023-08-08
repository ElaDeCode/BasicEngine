#include "fileManager.h"
#include <stdio.h>
#include <stdlib.h>

int createBufferFromFile(char **dst, const char *path) {
  FILE *fptr;
  size_t filesize;

  /* open file */
  fptr = fopen(path, "rb");
  if (fptr == NULL) {
    printf("\t !! unable to open file\n");
    return 0;
  }

  /* calculate filesize */
  fseek(fptr, 0, SEEK_END);
  filesize = ftell(fptr);
  fseek(fptr, 0, SEEK_SET);

  /* allocate buffer */
  *dst = malloc(sizeof(char) * (filesize + 1));
  if (!dst) {
    printf("couldn't create buffer\n"
           "for file : %s\n",
           path);
    return 0;
  }
  fread(*dst, sizeof(char), filesize, fptr);

  /* finish string */
  (*dst)[filesize] = '\0';

  fclose(fptr);
  return filesize;
}