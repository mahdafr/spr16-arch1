#include <stdio.h> // for scanf/printf

#define NAME_LENGTH 10
struct person {
  char first_name[NAME_LENGTH + 1];
  char last_name[NAME_LENGTH + 1];
  int age;
  struct person* next_person;
};

enum field {
  first_name,
  last_name,
  age,
};
