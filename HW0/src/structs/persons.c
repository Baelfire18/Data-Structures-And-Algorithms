#include "persons.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Person* person_init(int id, int state) {
  Person* person = malloc(sizeof(Person));
  *person = (Person){
      .id = id,
      .state = state,
      .parent = NULL,
      .head = NULL,
      .tail = NULL,
      .prev = NULL,
      .next = NULL,
  };
  return person;
}

void person_print(Person* person) {
  printf("Hello %i %i", person->id, person->state);
}

Person* person_append_contact(Person* person, int other_id, int state) {
  Person* new_person = person_init(other_id, state);
  if (!person->head) {
    person->head = new_person;
  } else {
    new_person->prev = person->tail;
    person->tail->next = new_person;
  }
  person->tail = new_person;
  new_person->parent = person;
  return new_person;
}

Person* person_search_contact(Person* person, int id) {
  Person* current = person->head;
  while (current) {
    if (current->id == id) {
      return current;
    }
    current = current->next;
  }
  return NULL;
}

void person_recursive_inform(Person* person, int depth, FILE* output_file) {
  for (int i = 0; i < depth * 4; i++) {
    fprintf(output_file, " ");
  }
  fprintf(output_file, "%i:%i\n", person->id, person->state);
  Person* current = person->head;
  while (current) {
    person_recursive_inform(current, depth + 1, output_file);
    current = current->next;
  }
}

void person_delete(Person* person) {
  if (person->head) {
    person_delete(person->head);
  }
  if (person->next) {
    person_delete(person->next);
  }
  free(person);
}
