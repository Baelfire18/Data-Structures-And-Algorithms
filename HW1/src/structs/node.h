#include "pixel.h"

typedef struct node {
  int color;
  int size;
  Pixel* pixel_head;
  Pixel* pixel_tail;
  struct node* parent;
  struct node* head;
  struct node* tail;
  struct node* prev; 
  struct node* next;
} Node;


Node* node_init();
Pixel* search_for_first_pixel(Pixel** lista, int largo, int threshold);
int min_threshold(Pixel** lista, int largo);
void add_pixels_to_parent(Node* node, Pixel** lista, int largo, int threshold);
Pixel* search_for_first_pixel_2(Node* node, int threshold);
void min_threshold_2(Node* node);
void add_pixels(Node* node, Node* parent, Pixel* pixel);
int add(Pixel* pixel, int threshold);
Node* create_parent_node(int threshold, Pixel** lista, int largo);
void create_node(Node* parent, Pixel* pixel_inicial);
void populate(Node* node, int threshold);
void clear(Node* node);
void print_node(Node* node);
void delete_node(Node* node);
void genealogy(Node* node, int depth);
void area_filter(Node* node, int min_area, int threshold);
void delta_filter(Node* node, float max_delta);
