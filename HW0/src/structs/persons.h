#pragma once

typedef struct person {
  int id;
  int state;
  struct person* parent; // de quien te contagiaste
  struct person* head; // a quien contagiaste primero
  struct person* tail; // a quien contagiaste de último
  struct person* prev; 
  struct person* next;
} Person;


Person* person_init(int id, int state);
void person_print(Person* persona);
Person* person_append_contact(Person* person, int other_id, int state);
Person* person_search_contact(Person* person, int id);
void person_recursive_inform(Person* person, int depth, FILE* output_file);
void person_delete(Person* person);
