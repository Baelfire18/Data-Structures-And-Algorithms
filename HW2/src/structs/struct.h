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

typedef struct subimage {
  int large;
  struct pixel* first_pixel;
  int blacks;
  int pos;
  struct subimage* next;
  struct subimage* prev;
  struct subimage* last;
} SubImage;



Pixel* pixel_init(int color, int pos);
SubImage* subimage_init(int large, Pixel* pixel, int black, int pos);
void pixels_delete(Pixel** pixels, int size);
void sub_image_delete(SubImage* subimage);
int blacks (Pixel** lista, int origen, int n, int largo, int ancho);
