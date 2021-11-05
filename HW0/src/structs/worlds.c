#include <stdio.h>
#include <stdlib.h>
#include "worlds.h"

World* world_init(int n_countries) {
  World* world = malloc(sizeof(World));
  *world = (World) {
    .n_countries = n_countries,
    .n_regions_countries = calloc(n_countries, sizeof(int)),
    .countries = calloc(n_countries, sizeof(Person**)),
    .people_count = calloc(n_countries, sizeof(int*)), 
  };
  return world;
}

void world_create_region(World* world, int idx, int amount) {
  world->n_regions_countries[idx] = amount;
  world->countries[idx] = malloc(amount*sizeof(Person*));
  world->people_count[idx] = malloc(amount*sizeof(int));
  for (int i = 0; i < amount; i+=1) {
    Person* A = person_init(0, 2);
    world->countries[idx][i] = A;
    world->people_count[idx][i] = 1;
  }
}

Person* world_search(World* world, int country_idx, int region_idx, int depth, int* route) {
  Person* person = world->countries[country_idx][region_idx];
  for (int idx = 0; idx < depth; idx+=1){
    person = person_search_contact(person, route[idx]);
  }
  return person;
}

Person* world_add_contact(World* world, Person* person, int new_id) {
  int lacho = 0;
  if (person->state == 2) {
    lacho = 1;
  }
  else {
    lacho = 0;
  }
  person_append_contact(person, new_id, lacho);
  return person;
}

void world_add_contacts(World* world, int country_idx, int region_idx, int depth, int* route, int n_contacts) {
  Person* person = world_search(world, country_idx, region_idx, depth, route);
  for (int i = 0; i < n_contacts; i+=1) {
    int new_id = world->people_count[country_idx][region_idx];
    world_add_contact(world, person, new_id);
    world->people_count[country_idx][region_idx] += 1;
  }
}

void world_inform(World* world, int country_idx, int region_idx, FILE* output_file) {
  // fprintf(output_file, "INFORM %i %i\n", country_idx, region_idx);
  Person* person = world->countries[country_idx][region_idx];
  person_recursive_inform(person, 0, output_file);
}

void positive(World* world, int country_idx, int region_idx, int depth, int* route) {
  Person * person = world_search(world, country_idx, region_idx, depth, route);
  person->state = 2;
  // printf("\n%i\n", person->id);
  if (person->head) {
    Person* child = person->head;
    while (child) {
      child->state = 1;
      child = child->next;
    }
  }
}

void recovered(World* world, int country_idx, int region_idx, int depth, int* route) {
  Person* person = world_search(world, country_idx, region_idx, depth, route);
  person->state = 3;
}

void negative(World* world, int country_idx, int region_idx, int depth, int* route) {
  Person* person = world_search(world, country_idx, region_idx, depth, route);
  if (person->head) {
    person_delete(person->head);
  }
  // printf("TERMINE DE BORRAR\n");
  Person* papa = person->parent;
  if (papa->head == person && papa->tail != person) { 
    // el wn esta en la cabeza y no está solo
    // printf("1\n");
    papa->head = person->next;
    person->next->prev = NULL;
  } else if (papa->head != person && papa->tail == person) { 
    // el wn que esta al final pero no al principio
    // printf("2\n");
    papa->tail = person->prev;
    person->prev->next = NULL;
  } else if (papa->head != person && papa->tail != person) {
    // el wn no esta al final y tampoco al principio
    // printf("3\n");
    Person* antes = person->prev;
    Person* despues = person->next;
    antes->next = despues;
    despues->prev = antes;
  } else if (papa->head == person && papa->tail == person) {
    // el wn esta solo
    // printf("4\n");
    papa->head = NULL;
    papa->tail = NULL;
  }
  // printf("aaaaaaaaaaaaaaaaaa\n");
  free(person);
  // printf("bbbbbbbbbbbbbbbbb\n");
  
}

void statistics(Person* person,  FILE* output_file, int* lista) {
  recursion(person, lista);
  for (int i=0; i < 4; i+=1) {
    fprintf(output_file, "%i:%i\n", i, lista[i]);
  }
  // printf("--------------------------------\n");
}

void recursion(Person* person, int* lista) {
  lista[person->state] += 1;
  // printf("%i %i\n", person->id, person->state);
  if (person->head) {
    recursion(person->head, lista);
  }
  if (person->next) {
    recursion(person->next, lista);
  }
}

void correct(World* world, int country_idx, int region_idx, int depth_1, int* route_1, int depth_2, int* route_2) {
  Person* person_1 = world_search(world, country_idx, region_idx, depth_1, route_1);
  Person* person_2 = world_search(world, country_idx, region_idx, depth_2, route_2);
  Person* child_1 = person_1->head;
  Person* child_2 = person_2->head;
  // printf("WENLO\n");
  // printf("%i %i\n", child_1->id, child_2->id);
  change(person_1, person_2, child_1);
  //printf("%i %i\n", person_1->head->id, person_2->head->id);
  change(person_2, person_1, child_2);
  // printf("%i %i\n", person_1->head->id, person_2->head->id);
  correct_number(person_1);
  correct_number(person_2);
}

void change(Person* person_1, Person* person_2, Person* child_1) {
  if (child_1) {
    // printf("%i\n", child_1->id);
    person_2->head = child_1;
    while (child_1) {
      child_1->parent = person_2;
      person_2->tail = child_1;
      child_1 = child_1->next;
    }
  } else {
    person_2->head = NULL;
    person_2->tail = NULL;
  }
}

void correct_number(Person* person) {
  if (person->head) {
    Person* child = person->head;
    while (child) {
      if (person->state == 2 && child->state == 0) {
        child->state = 1; 
      }
      child = child->next;
    }
  }
}
