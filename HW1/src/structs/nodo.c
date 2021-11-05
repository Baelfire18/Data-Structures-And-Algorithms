#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "nodo.h"

Nodo* nodo_init() {
  Nodo* nodo = malloc(sizeof(Nodo));
  *nodo = (Nodo) {
    .color = -300,
    .size = 0,
    .pixel_head = NULL,
    .pixel_tail = NULL,
    .parent = NULL,
    .head = NULL,
    .tail = NULL,
    .prev = NULL,
    .next = NULL,
  };
  return nodo;
}

Pixel* buscar_pixel_inicial(Pixel** lista, int largo, int umbral) {
  for (int i = 0; i < largo; i++) {
    if (lista[i]->color > umbral) {
      return lista[i];
    }
  }
  printf("Parece ninguno cumplia");
}

int min_umbral(Pixel** lista, int largo) {
  int chebi = 300;
  for (int i = 0; i < largo; i++) {
    // printf("%i\n", lista[i]->color);
    if (lista[i]->color < chebi && !lista[i]->asignado) {
      chebi = lista[i]->color;
    }
  }
  return chebi;
}

void agregar_pixeles_padre(Nodo* nodo, Pixel** lista, int largo, int umbral) {
  for (int i = 0; i < largo; i++) {
    if (lista[i]->color == umbral && !lista[i]->asignado) {
      lista[i]->asignado = 1;
      if (!nodo->pixel_head) {
        nodo->pixel_head = lista[i];
      }
      else {
        lista[i]->prev = nodo->pixel_tail;
        nodo->pixel_tail->next = lista[i];
      }
      nodo->pixel_tail = lista[i];
      lista[i]->nodo = nodo;
    }
  }
}

Pixel* buscar_pixel_inicial_2(Nodo* nodo, int umbral) {
  // printf("Umbral es %i\n", umbral);
  Pixel* pixel = nodo->pixel_head;
  while (pixel) {
    // printf("%i %i %i\n", pixel->pos, pixel->color, pixel->asignado);
    if (pixel->color > umbral && !pixel->asignado) {
      return pixel;
    }
    pixel = pixel->next;
  }
  printf("\nWenlo420\n");
}

void min_umbral_2(Nodo* nodo) {
  Pixel* pixel = nodo->pixel_head;
  int umbral = nodo->pixel_head->color; 
  // printf("Umbral a superar es %i\n", umbral);
  while (pixel) {
    // printf("%i %i %i\n", pixel->pos, pixel->color, pixel->asignado);
    if (pixel->color < umbral) {
      umbral = pixel->color;
    }
    pixel = pixel->next;
  }
  nodo->color = umbral;
  // printf("pero, se le asigno el umbral %i\n", umbral);
}

void agregar_pixeles(Nodo* nodo, Nodo* parent, Pixel* pixel) {
  if (pixel) {
    // printf("Pixel es %i %i\n", pixel->pos, pixel->color);
    if (!pixel->asignado && pixel->color > parent->color) {
      pixel->asignado = 1;
      if (!nodo->pixel_head) {
        nodo->pixel_head = pixel;
      }
      else {
        pixel->prev = nodo->pixel_tail;
        nodo->pixel_tail->next = pixel;
      }
      nodo->pixel_tail = pixel;
      pixel->nodo = nodo;
      agregar_pixeles(nodo, parent, pixel->right);
      agregar_pixeles(nodo, parent, pixel->down);
      agregar_pixeles(nodo, parent, pixel->left);
      agregar_pixeles(nodo, parent, pixel->up);
    }
  }
}

int agregar(Pixel* pixel, int umbral) {
  if (pixel) {
    if (!pixel->asignado && pixel->color > umbral) {
        return 1;
    }
  }
  return 0;
}


Nodo* crear_nodo_padre(Pixel* pixel_inicial, int umbral, Pixel** lista, int largo) {
  Nodo* nodo = nodo_init();
  agregar_pixeles_padre(nodo, lista, largo, umbral);
  nodo->color = nodo->pixel_head->color;
  nodo->size = largo;
  // print_nodo(nodo);
  
  poblar(nodo, umbral);
  

  //Pixel* pixel = buscar_pixel_inicial_2(nodo, umbral);
  // re asigno y me quedo solo con los los del umbral re asigno next y prev de todos
  // printf("El primer pixel será %i %i\n\n", pixel->pos, pixel->color);
  
  // crear_nodo(nodo, pixel);

  return nodo;
}

void crear_nodo(Nodo* parent, Pixel* pixel_inicial) {
  Nodo* nodo = nodo_init();
  agregar_pixeles(nodo, parent, pixel_inicial);
  min_umbral_2(nodo);
  // print_nodo(nodo);

  if (!parent->head) {
    parent->head = nodo;
  }
  else {
    nodo->prev = parent->tail;
    parent->tail->next = nodo;
  }
  parent->tail = nodo;
  nodo->parent = parent;
}

void poblar(Nodo* nodo, int umbral) {
  Pixel* pixel = nodo->pixel_head;
  while (pixel) {
    if (agregar(pixel->right, umbral)) {
      crear_nodo(nodo, pixel->right);
    }
    if (agregar(pixel->down, umbral)) {
      crear_nodo(nodo, pixel->down);
    }
    if (agregar(pixel->left, umbral)) {
      crear_nodo(nodo, pixel->left);
    }
    if (agregar(pixel->up, umbral)) {
      crear_nodo(nodo, pixel->up);
    }
    pixel = pixel->next;
  }

  Nodo* trini_vargas = nodo->head;
  while (trini_vargas) {
    limpiar(trini_vargas);
    // print_nodo(trini_vargas);
    trini_vargas = trini_vargas->next;
  }

  Nodo* carlos_paredes = nodo->head;
  while(carlos_paredes) {
    poblar(carlos_paredes, carlos_paredes->color);

    carlos_paredes = carlos_paredes->next;
  }

}


void limpiar(Nodo* nodo) {
  // printf("parti a limpiar 420\n");
  int contador = 0;
  if (nodo) {
    int umbral = nodo->color;
    Pixel* pixel = nodo->pixel_head;
    while (pixel) {
      contador += 1;
      Pixel* aux = pixel->next;
      // printf("%i\n", pixel->pos);
      if (pixel->color != umbral) {
        pixel->asignado = 0;
        // printf("entre\n");
        if (nodo->pixel_head == pixel && nodo->pixel_tail != pixel) { 
          // el wn esta en la cabeza y no está solo
          // printf("1\n");
          nodo->pixel_head = pixel->next;
          pixel->next->prev = NULL;
        }
        else if (nodo->pixel_head != pixel && nodo->pixel_tail == pixel) { 
          // el wn que esta al final pero no al principio
          // printf("2\n");
          nodo->pixel_tail = pixel->prev;
          pixel->prev->next = NULL;
        }
        else if (nodo->pixel_head != pixel && nodo->pixel_tail != pixel) { 
          // el wn no esta al final y tampoco al principio
          // printf("3\n");
          Pixel* antes = pixel->prev;
          Pixel* despues = pixel->next;
          antes->next = despues;
          despues->prev = antes;
        }
        // else if (nodo->pixel_head == pixel && nodo->pixel_tail == pixel) { 
        //   // el wn esta solo
        //   // printf("4\n");
        //   nodo->pixel_head = NULL;
        //   nodo->pixel_tail = NULL;
        // }
        pixel->prev = NULL;
        pixel->next = NULL;
      }
      pixel = aux;
    }
  }
  nodo->size = contador;
}

void print_nodo(Nodo* nodo) {
  printf("El umbral de este nood es %i y su tamaño %i\n", nodo->color, nodo->size);
  Pixel* pixel = nodo->pixel_head;
  while (pixel) {
    printf("%i %i %i\n", pixel->pos, pixel->color, pixel->asignado);
    pixel= pixel->next;
  }
  printf("--------------------------------------\n");
}

void nodo_delete(Nodo* nodo) {
  if (nodo->head) {
    nodo_delete(nodo->head);
  }
  if (nodo->next) {
    nodo_delete(nodo->next);
  }
  free(nodo);
}

void genealogia(Nodo* nodo, int depth) {
  if (nodo) {
    for (int i = 0; i < depth*6; i+=1) {
      printf(" ");
    }
    printf("%i:%i\n", nodo->color, nodo->size);
  }
  if (nodo->head) {
    genealogia(nodo->head, depth+1);
  }
  if (nodo->next) {
    genealogia(nodo->next, depth);
  }
}


void area_filter(Nodo* nodo, int min_area, int umbral) {
  if (nodo) {
    // int chebi = vecindario_size(nodo, 0);
    // printf("Tamaño %i\n", nodo->size);
    if ((umbral >= nodo->color || min_area >= nodo->size )) {
      // colorean
      Pixel* pixel = nodo->pixel_head;
      while (pixel) {
        if (!nodo->parent) {
          pixel->color = 0;
          nodo->color = 0;
        }
        else {
          pixel->color = nodo->parent->color;
          nodo->color = nodo->parent->color;
        }
        pixel = pixel->next; 
      }
    }
    if (nodo->head) {
      area_filter(nodo->head, min_area, umbral);
    }
    if (nodo->next) {
      area_filter(nodo->next, min_area, umbral);
    }
  }
}

void delta_filter(Nodo* nodo, float max_delta) {
  if (nodo) {
    if (!nodo->parent) {
      nodo->color = 0;
      Pixel* pixel = nodo->pixel_head;
      while (pixel) {
        pixel->color = 0;
        pixel = pixel->next;
      }
      // printf("estoy haciendo negro al raíz!\n");
    }
    else {
      float delta = (float) (nodo->parent->size - nodo->size) / nodo->parent->size;
      if (delta >= max_delta) {
        // obtienen condicion
        Pixel* pixel = nodo->pixel_head;
        while (pixel) {
          pixel->color = nodo->parent->color;
          pixel = pixel->next; 
        }
        nodo->color = nodo->parent->color;
      }
    }
    if (nodo->head) {
      delta_filter(nodo->head, max_delta);
    }
    if (nodo->next) {
      delta_filter(nodo->next, max_delta);
    }
  }
}
