#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../imagelib/image.h"
#include "../structs/node.h"
#include "../structs/pixel.h"

int main(int argc, char** argv) {
  // We review the arguments
  if (argc < 4) {
    printf("Mode of use: %s <input.png> <output.png> <command> [args]\n", argv[0]);
    return 1;
  }

  // We load the original image from the file
  Image* image = img_png_read_from_file(argv[1]);

  /* Here we create de MaxTree of the image.   */

  // We instantiate all pixels in a list !
  Pixel** master_list = calloc(image->pixel_count, sizeof(Pixel*));
  for (int i = 0; i < image->pixel_count; i++) {
    master_list[i] = pixel_init(image->pixels[i], i);
  }

  // Here we assing the borders of each pixel
  for (int i = 0; i < image->pixel_count; i++) {
    // We assign the right side
    if ((i + 1) % image->width) {
      master_list[i]->right = master_list[i + 1];
    }
    // We assign the bottom side
    if (i < image->pixel_count - image->width) {
      master_list[i]->down = master_list[i + image->width];
    }
    // We assign the left side
    if ((i) % image->width) {
      master_list[i]->left = master_list[i - 1];
    }
    // We assign the top side
    if (i >= image->width) {
      master_list[i]->up = master_list[i - image->width];
    }
  }

  // Pixel* pixel = search_for_first_pixel(master_list, image->pixel_count, 0);
  // printf("The first pixel will be %i %i\n\n", pixel->pos, pixel->color);
  int min_color = min_threshold(master_list, image->pixel_count);
  // printf("And its color will be %i\n", min_color);
  Node* parent_node = create_parent_node(min_color, master_list, image->pixel_count);
  // genealogy(parent_node, 0);

  // We create a new image the same size for the output
  Image* new_img = calloc(1, sizeof(Image));
  *new_img = (Image){
      .height = image->height,
      .width = image->width,
      .pixel_count = image->pixel_count,
      .pixels = calloc(image->pixel_count, sizeof(int))};

  // We filter the tree and save it in an image, acording to each filter
  if (!strcmp("delta", argv[3])) {
    // Filtro DELTA
    float max_delta = atof(argv[4]);

    /* Here we implement delta filter    */
    delta_filter(parent_node, max_delta);
  } else if (!strcmp("area", argv[3])) {
    // Filtro AREA-COLOR
    int min_area = atoi(argv[4]);
    int threshold = atoi(argv[5]);

    /* Here we implement are filter  */
    area_filter(parent_node, min_area, threshold);
  }

  for (int i = 0; i < image->pixel_count; i++) {
    new_img->pixels[i] = master_list[i]->color;
  }

  // We export the new image
  printf("Guardando imagen en %s\n", argv[2]);
  img_png_write_to_file(new_img, argv[2]);
  // printf("Ready!\n");

  // We free the resources
  delete_pixels(master_list, image->pixel_count);
  delete_node(parent_node);
  img_png_destroy(image);
  img_png_destroy(new_img);

  // Finish succesfully
  return 0;
}
