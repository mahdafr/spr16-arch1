#include <stdlib.h> // for malloc
#include <errno.h>  // for errno 
#include "names.h"
#define pmalloc (struct person*)malloc(sizeof(struct person));

void get_names(struct person **people_head, char *file_name);
void print_names(struct person *people_head);
void free_people(struct person *people_head);

/*
 * main driver
 */
int main(void) {
  struct person *people_head = NULL;
  get_names(&people_head, "names.txt");
  print_names(people_head);
  free_people(people_head);
}

/*
 * Print a list of names
 * @param people_head start of the list to print
 */
void print_names(struct person *people_head) {
  struct person *current = people_head;
  
  printf("First name   Last name   Age\n");
  printf("----------------------------\n");
  while (current) {
    printf("%10s   %9s   %d\n", current->first_name, current->last_name, current->age);
    current = current->next_person;
  }
  putchar('\n');
} 

/*
 * Frees a list of people
 * @param people_head head of list of people to fail
 */
void free_people(struct person *people_head) {
  struct person *current = people_head, *next;
  
  // iterate through the list freeing entries
  // one at a time
  while (current) {
    next = current->next_person;
    free(current);
    current = next;
  }
}

/*
 * Reads a list of people from a file into the
 * specified list
 * @param head the head 
 * @param file_name name of the file to open
 */
void get_names(struct person **head, char *file_name) {
  struct person *current = NULL, *prev = NULL;
  
  FILE *names_file;

  // open a the specified file to read names
  names_file = fopen(file_name, "rt");
  if (!names_file) {
    printf("Error opening file aborting\n%s\n", strerror(errno));
    exit(1);
  }

  // read a person from a file
  current = pmalloc;
  while (fscanf(names_file, "%10s", current->first_name) > 0) {
    fscanf(names_file, "%10s", current->last_name);
    fscanf(names_file, "%d", &current->age);

    current->next_person = NULL;
    if (prev) {
      prev->next_person = current;
    } else {
      *head = current;
    }
    prev = current;
    // alloc the next entry
    current = pmalloc;
  }

  return;
}
