#pragma once

typedef struct pixel {
  int color;
  int pos;
  int asignado;
  struct nodo* nodo;
  struct pixel* left;
  struct pixel* right;
  struct pixel* down;
  struct pixel* up;
  struct pixel* prev; 
  struct pixel* next;
} Pixel;

Pixel* pixel_init(int color, int pos);
void pixels_delete(Pixel** pixel, int size);
