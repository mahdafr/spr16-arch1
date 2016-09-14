//Exercise 1-10. Write a program to copy its input to its output, replacing each tab by \t, each backspace by \b, and each backslash by \\. This makes tabs and backspaces visible in an unambiguous way.

#include <stdio.h>
int main(void) {
  char c = getchar(); printf("%c",c);
  while ( (c=getchar()) != EOF ) {
    if ( c=='\t' ) printf("\\t"); //ctrl-q
    else if ( c=='\b' ) printf("\\b"); //ctrl-h is backspace
    else if ( c=='\\' ) printf("\\\\"); //using \\ works
    else printf("%c", c); //printing the character
  }
  return 0;
}

//end of exercise 1-10
