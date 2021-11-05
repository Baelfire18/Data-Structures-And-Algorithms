#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../imagelib/image.h"
#include "../structs/nodo.h"
#include "../structs/pixel.h"


int main(int argc, char** argv) {
  // Revisamos los argumentos
  if(argc < 4) {
    printf("Modo de uso: %s <input.png> <output.png> <command> [args]\n", argv[0]);
    return 1;
  }

  // Cargamos la imagen original desde el archivo
  Image* image = img_png_read_from_file(argv[1]);

  /* ------------- POR IMPLEMENTAR -------------- */
  /* Aqui debes crear el MaxTree de la imagen.    */

  // Instanciamos todos los pixeles !
  Pixel** lista_master = calloc(image->pixel_count, sizeof(Pixel*));
  for (int i=0; i < image->pixel_count; i++) {
    lista_master[i] = pixel_init(image->pixels[i], i);
  }

  for (int i=0; i < image->pixel_count; i++) {
    if ( (i+1) % image->width) {
      lista_master[i]->right = lista_master[i+1];
      // printf("le asigno lado derecho a %i\n", lista_master[i]->pos);
    }
    if (i < image->pixel_count - image->width) {
      lista_master[i]->down = lista_master[i+image->width];
      // printf("le asigno lado abajo a %i\n", lista_master[i]->pos);
    }
    if ( (i) % image->width) {
      lista_master[i]->left = lista_master[i-1];        
      // printf("le asigno lado izquierdo a %i\n", lista_master[i]->pos);
    }
    if (i >= image->width) {
      lista_master[i]->up = lista_master[i-image->width];
      // printf("le asigno lado ariba a %i\n", lista_master[i]->pos);
    }
    //   if (i !=  image->pixel_count -1) {
    //     lista_master[i]->next = lista_master[i+1];
    //   }
    //   if (i !=  0) {
    //     lista_master[i]->prev = lista_master[i-1];
    //   }
    }
    
    int beli = 0;
    for (int i=0; i < image->height; i++) {
      for (int j=0; j < image->width; j++) {
        // printf("%*i", 4, lista_master[beli]->color);
        beli++;
      }
      // printf("\n");
    }
    Pixel* pixel = buscar_pixel_inicial(lista_master, image->pixel_count, 0);
    // printf("El primer pixel será %i %i\n\n", pixel->pos, pixel->color);
    int a = min_umbral(lista_master, image->pixel_count);
    // printf("Y el primer umbral %i\n", a);
    Nodo* nodo_padre = crear_nodo_padre(pixel, a, lista_master, image->pixel_count);
    // genealogia(nodo_padre, 0);
    // Creamos una nueva imagen de igual tamaño, para el output
    Image* new_img = calloc(1, sizeof(Image));
    *new_img = (Image) {
        .height = image->height,
        .width = image->width,
        .pixel_count = image->pixel_count,
        .pixels = calloc(image->pixel_count, sizeof(int))
    };

    // Filtramos el arbol y lo guardamos en la imagen, segun el filtro que corresponda
    if (! strcmp("delta", argv[3])) {
      // Filtro DELTA
      float max_delta = atof(argv[4]);

      /* ------------- POR IMPLEMENTAR -------------- */
      /* Aqui debes implementar el filtro delta y     */
      delta_filter(nodo_padre, max_delta);
      /* guardar la imagen filtrada en new_img.       */
    }
    else if (! strcmp("area", argv[3])) {
      // Filtro AREA-COLOR
      int min_area = atoi(argv[4]);
      int threshold = atoi(argv[5]);

      /* ------------- POR IMPLEMENTAR -------------- */
      /* Aqui debes implementar el filtro de area y   */
      area_filter(nodo_padre, min_area, threshold);
      /* guardar la imagen filtrada en new_img.       */
    }

    for (int i=0; i< image->pixel_count; i++) {
      new_img->pixels[i] = lista_master[i]->color;
    }

    // Exportamos la nueva imagen
    printf("Guardando imagen en %s\n", argv[2]);
    img_png_write_to_file(new_img, argv[2]);
    // printf("Listo!\n");

    // Liberamos los recursos
    pixels_delete(lista_master, image->pixel_count);
    nodo_delete(nodo_padre);
    img_png_destroy(image);
    img_png_destroy(new_img);

    // Terminamos exitosamente
    return 0;
}
