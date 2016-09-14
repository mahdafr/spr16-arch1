#include <stdio.h>
#include <stdlib.h>

void squeeze(char s1[], char s2[]);

int main(void) {
  char strArray[] = "This is a string";
  char remove[] = "isa";
  //outputting before modifying (debugging)
  printf("String 1 %s\n", strArray);
  squeeze(strArray, remove);
  printf("String 1 %s\n", strArray);
} //end main method

void squeeze(char strArray[], char remove[]) {
  //starting at first index of strArray (strIndex)
  //remIndex tracks which character to remove from strArray by checking its character in remove
  //check will track the current value
  int strIndex=0, remIndex, check;

  //now we traverse the strArray
  while ( strArray[strIndex] ) {
    remIndex = 0; //resetting remIndex to 0 with each iteration through strArray
    while ( remove[remIndex] ) {
      //is the character strArray[strIndex] the same as remove[remIndex]?
      if ( strArray[strIndex]==remove[remIndex] ) {
	check = strIndex;
	  while ( strArray[check] ) {
	    strArray[check] = strArray[check + 1];
	    ++check;
	  } //end while: changing the characters of the strArray
      } //end if: found the same character to remove
      remIndex++; //find next character to remove in the remove array
    } //end while: traversing remove array
    strIndex++;
  } //end while; traversing through strArray to modify it
} //end method: squeeze
