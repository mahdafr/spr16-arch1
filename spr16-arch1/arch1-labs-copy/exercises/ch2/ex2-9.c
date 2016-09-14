//Exercise 2-9: In a two's complement number system, x &= (x-1) deletes the rightmost 1-bit in x. Explain why. Use this observation to write a faster version of bitcount.
//int bitcount(unsigned x) {
  //int b;
  //for ( b-0 ; x!=0 ; x>>=1 )
    //if ( x & 01 ) b++;
  //return b;
//}

#include <stdio.h>

int bitCount2(unsigned x) {
  int b;
  //this for loop is modified to continue through the number bitwise until it is a 0
  for ( b=0 ; x!=0 ; x&=(x-1) )
    b++;
  return b;
}

int main(void) {
  printf("bitCount2(13) = %i\nbitCount2(17) = %i\n",bitCount2(13),bitCount2(17));
  return 0;
}
