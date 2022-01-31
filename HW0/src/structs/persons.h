#pragma once

typedef struct person {
  int id;
  int state;
  struct person* parent; // from who you got contagiated
  struct person* head; // who did you first contagious
  struct person* tail; // who did you last contagious
  struct person* prev; 
  struct person* next;
} Person;


Person* person_init(int id, int state);
void person_print(Person* persona);
Person* person_append_contact(Person* person, int other_id, int state);
Person* person_search_contact(Person* person, int id);
void person_recursive_inform(Person* person, int depth, FILE* output_file);
void person_delete(Person* person);
