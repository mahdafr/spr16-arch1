#include <stdlib.h> // for malloc
#include <errno.h>  // for errno 
#include "namesBST.h"
#include <string.h> //for string comparison

#define pmalloc (struct node*)malloc(sizeof(struct node));

void get_names(struct node **people_head, char *file_name);
void print_names(struct node *people_head);
void free_people(struct node *people_head);
void printNames(struct node *curr);
void insert(struct node **root,struct node *ptr);

int main(void) {
  struct node *people_head = NULL;
  get_names(&people_head, "names.txt");
  print_names(people_head);
  //free_people(people_head);
}

//Print the list of names in order
void print_names(struct node *people_head) {
  printf("First name   Last name   Age\n");
  printf("----------------------------\n");
  printNames(people_head);
}
void printNames(struct node *current) {
  if ( current == NULL ) return;
  printNames(current->leftChild);
  printf("%10s   %9s   %d\n", current->first_name, current->last_name, current->age);
  printNames(current->rightChild);
}

//Frees a list of people
void free_people(struct node *people_head) {
  if ( people_head == NULL ) return;
  free_people(people_head->leftChild);
  free_people(people_head->rightChild);
  people_head = NULL;
}

//Method to get the names
void get_names(struct node **head, char *file_name) {
  struct node *current = NULL;
  FILE *names_file;
  //open a the specified file to read names
  names_file = fopen(file_name, "rt");
  if (!names_file) {
    printf("Error opening file aborting\n%s\n", strerror(errno));
    exit(1);
  }
  //read a person from a file
  current = pmalloc;
  while (fscanf(names_file, "%10s", current->first_name) > 0) {
    fscanf(names_file, "%10s", current->last_name);
    fscanf(names_file, "%d", &current->age);
    //insert into the BST: from this node we created
    insert(head,current);
    current = pmalloc;
  }
  return;
}

//helper method: insert into the binary search tree
void insert(struct node **curr, struct node *tmp) {
  //if the current node to insert in is null, place the data here
  if ( *curr==NULL ) *curr = tmp;
  else {
    int c = strcmp(tmp->last_name,(*curr)->last_name);
    //if the last name is alphabetically AFTER this node: go right
    if ( c>0 ) insert(&(*curr)->rightChild,tmp);
    //if the last name is alphabetically BEFORE or EQUAL TO  this node: go left
    else insert(&(*curr)->leftChild,tmp);
  }
}
