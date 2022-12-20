#include "struct.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Pixel* pixel_init(int color, int pos) {
  Pixel* pixel = malloc(sizeof(Pixel));
  *pixel = (Pixel){
      .color = color,
      .pos = pos,
      .asignado = 0,
      .left = NULL,
      .right = NULL,
      .down = NULL,
      .up = NULL,
      .prev = NULL,
      .next = NULL,
  };
  return pixel;
}

SubImage* subimage_init(int large, Pixel* pixel, int blacks, int pos) {
  SubImage* subimage = malloc(sizeof(SubImage));
  *subimage = (SubImage){
      .large = large,
      .first_pixel = pixel,
      .blacks = blacks,
      .pos = pos,
      .prev = NULL,
      .next = NULL,
      .last = NULL,
  };
  return subimage;
}

void delete_pixels(Pixel** pixels, int size) {
  for (int i = 0; i < size; i++) {
    free(pixels[i]);
  }
  free(pixels);
}

void sub_image_delete(SubImage* subimage) {
  if (subimage->next) {
    sub_image_delete(subimage->next);
    free(subimage);
  } else {
    free(subimage);
  }
}

int blacks(Pixel** list, int origen, int n, int height, int width) {
  int counter = 0;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (list[origen + i * n + j]->color == 0) {
        counter++;
      }
    }
  }
  return counter;
}
