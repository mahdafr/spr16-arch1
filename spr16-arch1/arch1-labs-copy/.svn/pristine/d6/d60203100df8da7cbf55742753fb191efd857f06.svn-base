//Exercise 1-20: Write a program detab that replaces tabs in the input with the proper number of blanks to space to the next tab stop. Assume a fixed set of tab stops, say every n columns. Should n be a variable or a symbolic parameter?

#include <stdio.h>

void detab() {
  char c = ' ';
  int columns = 0;
  while ( (c=getchar()) != EOF ) {
    columns++;
    if ( c=='\t' ) {
      for ( int i=columns%8 ; i<8 ; i++ ) {
	printf(" "); //fill the remainder of spaces to the next even column (every 8)
      } //end if: outputting remaining ' 's
      columns = 0;
    } //end if: the input is a tab
    if ( c=='\n' ) columns = 0; //reset the counter if new line
    printf("%c",c);
  } //end while: taking continuous input
}

int main(void) {
  detab();
  return 0;
}
