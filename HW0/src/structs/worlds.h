#pragma once
#include "persons.h"

typedef struct world {
  int n_countries;
  int* n_regions_countries;
  Person*** countries;
  int** people_count;
} World;


World* world_init(int n_countries);
void world_create_region(World* world, int idx, int amount);
Person* world_search(World* world, int country_idx, int region_idx, int depth, int* route);
Person* world_add_contact(World* world, Person* person, int new_id);
void world_add_contacts(World* world, int country_idx, int region_idx, int depth, int* route, int n_contacts);
void world_inform(World* world, int country_idx, int region_idx, FILE* output_file);
void positive(World* world, int country_idx, int region_idx, int depth, int* route);
void negative(World* world, int country_idx, int region_idx, int depth, int* route);
void recovered(World* world, int country_idx, int region_idx, int depth, int* route);
void negative(World* world, int country_idx, int region_idx, int depth, int* route);
void statistics(Person* person,  FILE* output_file, int* lista);
void recursion(Person* person, int* lista);
void correct(World* world, int country_idx, int region_idx, int depth_1, int* route_1, int depth_2, int* route_2);
void change(Person* person_1, Person* person_2, Person* child_1);
void correct_number(Person* person);
