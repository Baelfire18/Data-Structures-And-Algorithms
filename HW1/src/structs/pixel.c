#include "pixel.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Pixel* pixel_init(int color, int pos) {
  Pixel* pixel = malloc(sizeof(Pixel));
  *pixel = (Pixel){
      .color = color,
      .pos = pos,
      .assigned = 0,
      .left = NULL,
      .right = NULL,
      .down = NULL,
      .up = NULL,
      .prev = NULL,
      .next = NULL,
  };
  return pixel;
}

void delete_pixels(Pixel** pixels, int size) {
  for (int i = 0; i < size; i++) {
    free(pixels[i]);
  }
  free(pixels);
}
