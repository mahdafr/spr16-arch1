//Exercise 2-1. Write a program to determine the ranges of char, short, int, and long variables, both signed and unsigned, by printing appropriate values from standard headers and by direct computation. Harder if you compute them: determine the ranges of the various floating-point types.

#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(void) {
  unsigned char cUnsigned = 0;
  signed char cSigned = 0;
  unsigned short sUnsigned = 0;
  signed short sSigned = 0;
  unsigned int iUnsigned = 0;
  signed int iSigned = 0;
  unsigned long lUnsigned = 0;
  signed long lSigned = 0;

  //to find the min for an unsigned variable, we output the current value: 0
  printf("Unsigned char min:  %d\nUnsigned short min: %d\nUnsigned int min:   %d\nUnsigned long min:  %d\n\n",cUnsigned,sUnsigned,iUnsigned,lUnsigned);
  
  //to find the max for an unsigned variable, we use 1's complement
  cUnsigned = ~cUnsigned; printf("Unsigned char max:  %d\n",cUnsigned);
  sUnsigned = ~sUnsigned; printf("Unsigned short max: %d\n",sUnsigned);
  iUnsigned = ~iUnsigned; printf("Unsigned int max:   %u\n",iUnsigned);
  lUnsigned = ~lUnsigned; printf("Unsigned long max:  %u\n\n",lUnsigned);
  
  //to find the min for a signed variable, we shift left 7 bits after initializing to -1
  cSigned = -1; cSigned = cSigned << 7;
  sSigned = -1; sSigned = sSigned << 15;
  iSigned = -1; iSigned = iSigned << 31;
  lSigned = -1; lSigned = lSigned << 31;
  printf("Signed char min:  %d\nSigned short min: %d\nSigned int min:   %d\nSigned long min:  %d\n\n",cSigned,sSigned,iSigned,lSigned);

  //to find the max for a signed variable, we shift one bit (done for min) and perform 1's complement
  cSigned = ~ cSigned;
  sSigned = ~ sSigned;
  iSigned = ~ iSigned;
  lSigned = ~ lSigned;
  printf("Signed char max:  %d\nSigned short max: %d\nSigned int max:   %d\nSigned long max:  %d\n\n",cSigned,sSigned,iSigned,lSigned);
}
