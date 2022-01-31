#pragma once

/** Represents an image with a list of monocromatic pixels */
typedef struct image {
  int* pixels;
  int width;
  int height;
  int pixel_count;
} Image;


Image* img_png_read_from_file(char* filename);
void img_png_write_to_file(Image* img, char* filename);
void img_png_destroy(Image* img);
