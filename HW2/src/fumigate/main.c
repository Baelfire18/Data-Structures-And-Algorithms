#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../imagelib/image.h"
#include "../structs/struct.h"

#define BLACK 0
#define WHITE 127
#define GRAY 64


int main(int argc, char** argv) {  
  if (argc != 2) {
    printf("Modo de uso: %s INPUT \n", argv[0]);
    printf("Donde:\n");
    printf("\tINPUT es la ruta del archivo de input\n");
    return 1;
  }

  /* Abrimos el archivo de input */
  FILE* input_file = fopen(argv[1], "r");

  /* Leemos la ruta de la imagen principal */
  char filename[32];
  fscanf(input_file, "%s", filename);
  /* Abrimos la imagen principal */
  Image* image = img_png_read_from_file(filename);
  int n = image->height;

  /* Aca instanciamos los pixeles */
  
  Pixel** lista_master = calloc(image->pixel_count, sizeof(Pixel*));
  for (int i=0; i < image->pixel_count; i++) {
    lista_master[i] = pixel_init(image->pixels[i], i);
  }

  for (int i=0; i < image->pixel_count; i++) {
    if ((i+1) % image->width) {
      lista_master[i]->right = lista_master[i+1];
    }
    if (i < image->pixel_count - image->width) {
      lista_master[i]->down = lista_master[i+image->width];
    }
    if ((i) % image->width) {
      lista_master[i]->left = lista_master[i-1];
    }
    if (i >= image->width) {
      lista_master[i]->up = lista_master[i-image->width];
    }
  }

  /* Aca creamos la tabla de hash */
  int size_size_array = n + 1;
  SubImage*** size_array = calloc(size_size_array, sizeof(SubImage**));
  int* size_size_size_array = calloc(size_size_array, sizeof(int));

  for (int size = 0; size < n+1; size++) { // Recorre el size_array (todos los tamaños)
    int valor = (size + 2) * (size + 2) + 1;
    size_size_size_array[size] = valor;
    size_array[size] = calloc(valor, sizeof(SubImage*));
    int actual = 0;
    int viejo = 0;
    for (int j = 0; j < n*n; j++) { // Recorre todos los pixeles N x N
      if ( j % n + (size+2) <= n && j + (size+1) * n <= n * n -1) {        
        //printf("Pixel: %i Tamaño: %i\n", j, size + 2);
        if (j % n == 0) {
          //printf("Primero %i %i\n", j, size + 2);
          actual = blacks (lista_master,j,  n, size+2, size+2);
        } else {
          int check = j + size+1; 
          //printf("%i %i %i %i %i \n", j, check, n, size+2, 1);
          int nuevo = blacks (lista_master, check, n, size+2, 1);
          //printf("dsadasdasdasd %i\n", nuevo);
          actual = actual - viejo + nuevo;
        }
        //printf("Negros %i\n\n", actual);
        SubImage* wenlo = subimage_init(size + 2, lista_master[j], actual, j);
        if (size_array[size][actual]) {
          // size_array[size][actual]->next = wenlo;
          wenlo->prev = size_array[size][actual]->last;
          size_array[size][actual]->last->next = wenlo;
          size_array[size][actual]->last = wenlo;
        } else {
          size_array[size][actual] = wenlo;
          wenlo->last = wenlo;
        }
        viejo = blacks (lista_master, j, n, size+2, 1);
      } else {
        actual = 0;
        viejo = 0;
      }
    }
  }

  /* Leemos cada una de las consultas */
  int Q;
  char query_in[32];
  char query_out[32];
  fscanf(input_file, "%d", &Q);


  for (int q = 0; q < Q; q++) {
    /* Leemos las rutas de las imagenes */
    fscanf(input_file, "%s", query_in);
    fscanf(input_file, "%s", query_out);

    /* Abrimos la imagen de consulta de input */
    Image* query_image = img_png_read_from_file(query_in);

    /* Creamos una nueva imagen en blanco con las mismas dimensiones que la original */
    Image *out_image = calloc(1, sizeof(Image));
    out_image->height = image->height;
    out_image->width = image->width;
    out_image->pixel_count = image->pixel_count;
    out_image->pixels = calloc(image->pixel_count, sizeof(int));

    // TRANSFORMO AL BICHO EN PIXELES && CUENTO SUS NEGROS && TAMAÑO DEL BICHO
    Pixel** lista_bicho = calloc(query_image->pixel_count, sizeof(Pixel*));
    for (int i=0; i < query_image->pixel_count; i++) {
      lista_bicho[i] = pixel_init(query_image->pixels[i], i);
    }
    int negras_bicho = blacks(lista_bicho, 0, query_image->height, query_image->height, query_image->height);
    int cuantas = query_image->width;
    

    // ME METO AL ARRAY ITERO POR LAS SUBIMAGES DE LA LISTA LIGADA CONSTRUYENDO LA SUBIMAGEN CADA VEZ
    //printf("%i %i \n", cuantas-2, negras_bicho);
    SubImage* wenla = size_array[cuantas-2][negras_bicho];
    while (wenla) {
      int pos_inicial = wenla->pos;
      //printf("cacuuuuu %i %i\n", pos_inicial, wenla->blacks);
      int iguales = 1;
      for (int i = 0; i < wenla->large; i++) {
        for (int j = 0; j < wenla->large; j++) {
          Pixel* pixel_lista_master = (lista_master[ pos_inicial + i * n + j ]);
          Pixel* pixel_lista_bicho = (lista_bicho[ 0 + i * query_image->width + j ]);
          if (! (pixel_lista_master->color == pixel_lista_bicho->color) && abs(pixel_lista_master->color - pixel_lista_bicho->color) != GRAY - BLACK ) {
            iguales = 0;
            i = wenla->large;
            j = wenla->large;
            break;
          }
        }
      }
      if (iguales) {
        //printf("Pos inicial del pixel inicial de la subimagen igual %i ?\n", pos_inicial);
        for (int i = 0; i < wenla->large; i++) {
          for (int j = 0; j < wenla->large; j++) {
            Pixel* pixel_lista_master = (lista_master[ pos_inicial + i * n + j ]);
            // Pixel* pixel_lista_bicho = (lista_bicho[ 0 + i * n + j ]);
            if (pixel_lista_master->color == BLACK) {
              pixel_lista_master->color =  GRAY;
            }
          }
        }
      }
      wenla = wenla->next; // Siguiente subimagen
    }

    /* pintamos los pixeles de su color final (borrar las siguientes tres lineas)*/
      // out_image->pixels[0] = BLACK;
      // out_image->pixels[4] = WHITE; 
      // out_image->pixels[5] = GRAY;
    for (int i=0; i< out_image->pixel_count; i++) {
      out_image->pixels[i] = lista_master[i]->color;
    }

    /* Escribimos la imagen de output*/
    img_png_write_to_file(out_image, query_out);

    /* pintamos los pixeles grises a negros */
    for (int i=0; i< n * n; i++) {
      if (lista_master[i]->color == GRAY) {
        lista_master[i]->color = BLACK;
      }
    }

    /* Liberamos la memoria de las imagenes*/
    pixels_delete(lista_bicho, query_image->pixel_count);
    img_png_destroy(query_image);
    img_png_destroy(out_image);
  
  }
  
  pixels_delete(lista_master, image->pixel_count);

  for (int i = 0; i < size_size_array; i ++) {
    for (int j = 0; j < size_size_size_array[i]; j ++) {
      if (size_array[i][j]) {
        sub_image_delete(size_array[i][j]);
      }
    }
    free(size_array[i]);
  }
  free(size_array);
  free(size_size_size_array);

  /* Liberamos la memoria de la imagen principal */
  img_png_destroy(image);
  /* Cerramos el archivo de input */
  fclose(input_file);


  return 0;
}
