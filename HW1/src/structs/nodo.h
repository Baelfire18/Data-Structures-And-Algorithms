#include "pixel.h"

typedef struct nodo {
  int color;
  int size;
  Pixel* pixel_head;
  Pixel* pixel_tail;
  struct nodo* parent; // de quien te contagiaste
  struct nodo* head; // a quien contagiaste primero
  struct nodo* tail; // a quien contagiaste de último
  struct nodo* prev; 
  struct nodo* next;
} Nodo;

Nodo* nodo_init();
Pixel* buscar_pixel_inicial(Pixel** lista, int largo, int umbral);
int min_umbral(Pixel** lista, int largo);
void agregar_pixeles_padre(Nodo* nodo, Pixel** lista, int largo, int umbral);
Pixel* buscar_pixel_inicial_2(Nodo* nodo, int umbral);
void min_umbral_2(Nodo* nodo);
void agregar_pixeles(Nodo* nodo, Nodo* parent, Pixel* pixel);
int agregar(Pixel* pixel, int umbral);
Nodo* crear_nodo_padre(Pixel* pixel_inicial, int umbral, Pixel** lista, int largo);
void crear_nodo(Nodo* parent, Pixel* pixel_inicial);
void poblar(Nodo* nodo, int umbral);
void limpiar(Nodo* nodo);
void print_nodo(Nodo* nodo);
void nodo_delete(Nodo* nodo);
void genealogia(Nodo* nodo, int depth);
void area_filter(Nodo* nodo, int min_area, int umbral);
void delta_filter(Nodo* nodo, float max_delta);
