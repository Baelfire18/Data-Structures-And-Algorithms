#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../imagelib/image.h"
#include "../structs/struct.h"

#define BLACK 0
#define WHITE 127
#define GRAY 64

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("Mode of use: %s INPUT \n", argv[0]);
    printf("Where:\n");
    printf("\tINPUT is the input's file route\n");
    return 1;
  }

  /* We open the input file */
  FILE* input_file = fopen(argv[1], "r");

  /* We read the route of the main image file */
  char filename[32];
  fscanf(input_file, "%s", filename);
  /* We open the main image */
  Image* image = img_png_read_from_file(filename);
  int n = image->height;

  /* Here we iniciate their pixels */
  Pixel** master_list = calloc(image->pixel_count, sizeof(Pixel*));
  for (int i = 0; i < image->pixel_count; i++) {
    master_list[i] = pixel_init(image->pixels[i], i);
  }

  for (int i = 0; i < image->pixel_count; i++) {
    if ((i + 1) % image->width) {
      master_list[i]->right = master_list[i + 1];
    }
    if (i < image->pixel_count - image->width) {
      master_list[i]->down = master_list[i + image->width];
    }
    if ((i) % image->width) {
      master_list[i]->left = master_list[i - 1];
    }
    if (i >= image->width) {
      master_list[i]->up = master_list[i - image->width];
    }
  }

  /* Aca creamos la tabla de hash */
  int size_size_array = n + 1;
  SubImage*** size_array = calloc(size_size_array, sizeof(SubImage**));
  int* size_size_size_array = calloc(size_size_array, sizeof(int));

  // Recorre el size_array (todos los tamaños)
  for (int size = 0; size < n + 1; size++) {
    int valor = (size + 2) * (size + 2) + 1;
    size_size_size_array[size] = valor;
    size_array[size] = calloc(valor, sizeof(SubImage*));
    int actual = 0;
    int viejo = 0;
    // Recorre todos los pixeles N x N
    for (int j = 0; j < n * n; j++) {
      if (j % n + (size + 2) <= n && j + (size + 1) * n <= n * n - 1) {
        // printf("Pixel: %i Tamaño: %i\n", j, size + 2);
        if (j % n == 0) {
          // printf("Primero %i %i\n", j, size + 2);
          actual = blacks(master_list, j, n, size + 2, size + 2);
        } else {
          int check = j + size + 1;
          // printf("%i %i %i %i %i \n", j, check, n, size+2, 1);
          int nuevo = blacks(master_list, check, n, size + 2, 1);
          // printf("dsadasdasdasd %i\n", nuevo);
          actual = actual - viejo + nuevo;
        }
        // printf("Negros %i\n\n", actual);
        SubImage* wenlo = subimage_init(size + 2, master_list[j], actual, j);
        if (size_array[size][actual]) {
          // size_array[size][actual]->next = wenlo;
          wenlo->prev = size_array[size][actual]->last;
          size_array[size][actual]->last->next = wenlo;
          size_array[size][actual]->last = wenlo;
        } else {
          size_array[size][actual] = wenlo;
          wenlo->last = wenlo;
        }
        viejo = blacks(master_list, j, n, size + 2, 1);
      } else {
        actual = 0;
        viejo = 0;
      }
    }
  }

  /* We read each query */
  int Q;
  char query_in[32];
  char query_out[32];
  fscanf(input_file, "%d", &Q);

  for (int q = 0; q < Q; q++) {
    // We read the images files //
    fscanf(input_file, "%s", query_in);
    fscanf(input_file, "%s", query_out);

    // We open the image of the query //
    Image* query_image = img_png_read_from_file(query_in);

    // We create a new black image of the sizes of the original one //
    Image* out_image = calloc(1, sizeof(Image));
    out_image->height = image->height;
    out_image->width = image->width;
    out_image->pixel_count = image->pixel_count;
    out_image->pixels = calloc(image->pixel_count, sizeof(int));

    // TRANSFORMO AL BICHO EN PIXELES && CUENTO SUS NEGROS && TAMAÑO DEL BICHO
    Pixel** bug_list = calloc(query_image->pixel_count, sizeof(Pixel*));
    for (int i = 0; i < query_image->pixel_count; i++) {
      bug_list[i] = pixel_init(query_image->pixels[i], i);
    }
    int negras_bicho = blacks(bug_list, 0, query_image->height, query_image->height, query_image->height);
    int cuantas = query_image->width;

    // ME METO AL ARRAY ITERO POR LAS SUBIMAGES DE LA LISTA LIGADA CONSTRUYENDO LA SUBIMAGEN CADA VEZ
    // printf("%i %i \n", cuantas-2, negras_bicho);
    SubImage* wenla = size_array[cuantas - 2][negras_bicho];
    while (wenla) {
      int pos_inicial = wenla->pos;
      // printf("cacuuuuu %i %i\n", pos_inicial, wenla->blacks);
      int iguales = 1;
      for (int i = 0; i < wenla->large; i++) {
        for (int j = 0; j < wenla->large; j++) {
          Pixel* pixel_master_list = (master_list[pos_inicial + i * n + j]);
          Pixel* pixel_bug_list = (bug_list[0 + i * query_image->width + j]);
          if (!(pixel_master_list->color == pixel_bug_list->color) && abs(pixel_master_list->color - pixel_bug_list->color) != GRAY - BLACK) {
            iguales = 0;
            i = wenla->large;
            j = wenla->large;
            break;
          }
        }
      }
      if (iguales) {
        // printf("Pos inicial del pixel inicial de la subimagen igual %i ?\n", pos_inicial);
        for (int i = 0; i < wenla->large; i++) {
          for (int j = 0; j < wenla->large; j++) {
            Pixel* pixel_master_list = (master_list[pos_inicial + i * n + j]);
            // Pixel* pixel_bug_list = (bug_list[ 0 + i * n + j ]);
            if (pixel_master_list->color == BLACK) {
              pixel_master_list->color = GRAY;
            }
          }
        }
      }
      wenla = wenla->next;   // Siguiente subimagen
    }
    for (int i = 0; i < out_image->pixel_count; i++) {
      out_image->pixels[i] = master_list[i]->color;
    }

    /* Escribimos la imagen de output*/
    img_png_write_to_file(out_image, query_out);

    /* pintamos los pixeles grises a negros */
    for (int i = 0; i < n * n; i++) {
      if (master_list[i]->color == GRAY) {
        master_list[i]->color = BLACK;
      }
    }
    /* Liberamos la memoria de las imagenes*/
    delete_pixels(bug_list, query_image->pixel_count);
    img_png_destroy(query_image);
    img_png_destroy(out_image);
  }

  delete_pixels(master_list, image->pixel_count);

  for (int i = 0; i < size_size_array; i++) {
    for (int j = 0; j < size_size_size_array[i]; j++) {
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
