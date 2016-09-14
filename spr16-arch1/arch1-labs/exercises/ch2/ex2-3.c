//Exercise 2-3: Write the function htoi(s), which converts a string of hexadecimal digits (including an optional 0x or 0X) into its equivalent integer value. The allowable digits are 0 through 9, a through f, and A through F.

#include <stdio.h>
#include <math.h>

int htoi(char s[]) {
  //in this method, we convert from hexadecimal to integer
  int theNumber = 0; int val;
  for ( int i=0 ; s[i]!='\0' ; i++ ) {
    theNumber *= 16;
    //traverse the string of characters to build theNumber
    switch ( s[i] ) {
    case 'A': case 'a':
      theNumber += 10;
      break;
    case 'B': case 'b':
      theNumber += 11;
      break;
    case 'C': case 'c':
      theNumber += 12;
      break;
    case 'D': case 'd':
      theNumber += 13;
      break;
    case 'E': case 'e':
      theNumber += 14;
      break;
    case 'F': case 'f':
      theNumber += 15;
      break;
      //reading an X or x is optional and does not count in decimal
    case 'X': case 'x':
      theNumber = theNumber/16;
      break;
      //reading a 0 in the first iteration does not count in decimal
    case '0':
      if ( i==1 ) theNumber = theNumber/16;
      break;
    default:
      val = s[i] - '0';
      theNumber += val;
    } //end switch: character being read
  } //end for: traversing the string
  return theNumber;
}

int main(void) {
  int hToI = htoi("0xA");
  printf("%d\n",hToI);
  return 0;
}
