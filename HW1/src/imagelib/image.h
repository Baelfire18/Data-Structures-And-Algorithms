#pragma once

struct image {
  // Matriz de pixeles que corresponde a la imagen
  int* pixels;
  // Ancho de la imagen
  int width;
  // Alto de la imagen
  int height;
  // Pixeles totales
  int pixel_count;
};
/** Representa una imagen como una lista de pixeles monocromáticos */
typedef struct image Image;

/** Lee un archivo .png y entrega la imagen */
Image* img_png_read_from_file (char* filename);

/** Escribe el contenido de una imagen como archivo .png */
void   img_png_write_to_file  (Image* img, char* filename);

/** Libera los recursos asociados a la imagen */
void   img_png_destroy        (Image* img);
