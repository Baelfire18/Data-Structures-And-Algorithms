#include "node.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node* node_init() {
  Node* node = malloc(sizeof(Node));
  *node = (Node){
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
  return node;
}

// Unused function
Pixel* search_for_first_pixel(Pixel** list, int length, int threshold) {
  for (int i = 0; i < length; i++) {
    if (list[i]->color > threshold) {
      return list[i];
    }
  }
  printf("It's seems none of them fullfield");
}

int min_threshold(Pixel** list, int length) {
  int minimun = 300;
  for (int i = 0; i < length; i++) {
    if (list[i]->color < minimun && !list[i]->assigned) {
      minimun = list[i]->color;
    }
  }
  return minimun;
}

Node* create_parent_node(int threshold, Pixel** list, int lenght) {
  Node* node = node_init();
  add_pixels_to_parent(node, list, lenght, threshold);
  node->color = node->pixel_head->color;
  node->size = lenght;
  populate(node, threshold);
  return node;
}

void add_pixels_to_parent(Node* node, Pixel** list, int lenght, int threshold) {
  for (int i = 0; i < lenght; i++) {
    if (list[i]->color == threshold && !list[i]->assigned) {
      list[i]->assigned = 1;
      if (!node->pixel_head) {
        node->pixel_head = list[i];
      } else {
        list[i]->prev = node->pixel_tail;
        node->pixel_tail->next = list[i];
      }
      node->pixel_tail = list[i];
      list[i]->node = node;
    }
  }
}

void populate(Node* node, int threshold) {
  Pixel* pixel = node->pixel_head;
  while (pixel) {
    if (add(pixel->right, threshold)) {
      create_node(node, pixel->right);
    }
    if (add(pixel->down, threshold)) {
      create_node(node, pixel->down);
    }
    if (add(pixel->left, threshold)) {
      create_node(node, pixel->left);
    }
    if (add(pixel->up, threshold)) {
      create_node(node, pixel->up);
    }
    pixel = pixel->next;
  }

  // We clean head node
  Node* aux_node = node->head;
  while (aux_node) {
    clear(aux_node);
    aux_node = aux_node->next;
  }

  // We populate head children
  aux_node = node->head;
  while (aux_node) {
    populate(aux_node, aux_node->color);
    aux_node = aux_node->next;
  }
}

int add(Pixel* pixel, int threshold) {
  if (pixel) {
    if (!pixel->assigned && pixel->color > threshold) {
      return 1;
    }
  }
  return 0;
}

void create_node(Node* parent, Pixel* pixel_inicial) {
  Node* node = node_init();
  add_pixels(node, parent, pixel_inicial);
  min_threshold_2(node);
  if (!parent->head) {
    parent->head = node;
  } else {
    node->prev = parent->tail;
    parent->tail->next = node;
  }
  parent->tail = node;
  node->parent = parent;
}

void add_pixels(Node* node, Node* parent, Pixel* pixel) {
  if (pixel) {
    // printf("Pixel is %i %i\n", pixel->pos, pixel->color);
    if (!pixel->assigned && pixel->color > parent->color) {
      pixel->assigned = 1;
      if (!node->pixel_head) {
        node->pixel_head = pixel;
      } else {
        pixel->prev = node->pixel_tail;
        node->pixel_tail->next = pixel;
      }
      node->pixel_tail = pixel;
      pixel->node = node;
      add_pixels(node, parent, pixel->right);
      add_pixels(node, parent, pixel->down);
      add_pixels(node, parent, pixel->left);
      add_pixels(node, parent, pixel->up);
    }
  }
}

void min_threshold_2(Node* node) {
  Pixel* pixel = node->pixel_head;
  int threshold = node->pixel_head->color;
  // printf("threshold a superar es %i\n", threshold);
  while (pixel) {
    // printf("%i %i %i\n", pixel->pos, pixel->color, pixel->assigned);
    if (pixel->color < threshold) {
      threshold = pixel->color;
    }
    pixel = pixel->next;
  }
  node->color = threshold;
  // printf("pero, se le asigno el threshold %i\n", threshold);
}

// Unused function
Pixel* search_for_first_pixel_2(Node* node, int threshold) {
  // printf("threshold es %i\n", threshold);
  Pixel* pixel = node->pixel_head;
  while (pixel) {
    // printf("%i %i %i\n", pixel->pos, pixel->color, pixel->assigned);
    if (pixel->color > threshold && !pixel->assigned) {
      return pixel;
    }
    pixel = pixel->next;
  }
  printf("\nWenlo420\n");
}

void clear(Node* node) {
  int counter = 0;
  if (node) {
    int threshold = node->color;
    Pixel* pixel = node->pixel_head;
    while (pixel) {
      counter += 1;
      Pixel* aux = pixel->next;
      if (pixel->color != threshold) {
        pixel->assigned = 0;
        if (node->pixel_head == pixel && node->pixel_tail != pixel) {
          node->pixel_head = pixel->next;
          pixel->next->prev = NULL;
        } else if (node->pixel_head != pixel && node->pixel_tail == pixel) {
          node->pixel_tail = pixel->prev;
          pixel->prev->next = NULL;
        } else if (node->pixel_head != pixel && node->pixel_tail != pixel) {
          Pixel* before = pixel->prev;
          Pixel* after = pixel->next;
          before->next = after;
          after->prev = before;
        }
        pixel->prev = NULL;
        pixel->next = NULL;
      }
      pixel = aux;
    }
  }
  node->size = counter;
}

void print_node(Node* node) {
  printf("The threshold of this node is %i and its size is %i\n", node->color, node->size);
  Pixel* pixel = node->pixel_head;
  while (pixel) {
    printf("%i %i %i\n", pixel->pos, pixel->color, pixel->assigned);
    pixel = pixel->next;
  }
}

void delete_node(Node* node) {
  if (node->head) {
    delete_node(node->head);
  }
  if (node->next) {
    delete_node(node->next);
  }
  free(node);
}

void genealogy(Node* node, int depth) {
  if (node) {
    for (int i = 0; i < depth * 6; i += 1) {
      printf(" ");
    }
    printf("%i:%i\n", node->color, node->size);
  }
  if (node->head) {
    genealogy(node->head, depth + 1);
  }
  if (node->next) {
    genealogy(node->next, depth);
  }
}

// Filters
void area_filter(Node* node, int min_area, int threshold) {
  if (node) {
    if (threshold >= node->color || min_area >= node->size) {
      Pixel* pixel = node->pixel_head;
      while (pixel) {
        if (!node->parent) {
          pixel->color = 0;
          node->color = 0;
        } else {
          pixel->color = node->parent->color;
          node->color = node->parent->color;
        }
        pixel = pixel->next;
      }
    }
    if (node->head) {
      area_filter(node->head, min_area, threshold);
    }
    if (node->next) {
      area_filter(node->next, min_area, threshold);
    }
  }
}

void delta_filter(Node* node, float max_delta) {
  if (node) {
    if (!node->parent) {
      node->color = 0;
      Pixel* pixel = node->pixel_head;
      while (pixel) {
        pixel->color = 0;
        pixel = pixel->next;
      }
      // printf("Macking the root black!\n");
    } else {
      float delta = (float)(node->parent->size - node->size) / node->parent->size;
      if (delta >= max_delta) {
        // They get the condition
        Pixel* pixel = node->pixel_head;
        while (pixel) {
          pixel->color = node->parent->color;
          pixel = pixel->next;
        }
        node->color = node->parent->color;
      }
    }
    if (node->head) {
      delta_filter(node->head, max_delta);
    }
    if (node->next) {
      delta_filter(node->next, max_delta);
    }
  }
}
