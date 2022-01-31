#pragma once

typedef struct pixel {
  int color;
  int pos;
  int assigned;
  struct node* node;
  struct pixel* left;
  struct pixel* right;
  struct pixel* down;
  struct pixel* up;
  struct pixel* prev; 
  struct pixel* next;
} Pixel;


Pixel* pixel_init(int color, int pos);
void delete_pixels(Pixel** pixel, int size);
