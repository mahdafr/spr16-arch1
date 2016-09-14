//Exercise 2-X: Implement the following functions which should work for reasonable values of bits and lsb from 0 to 32, inclusive. Your documentation should describe their theory of operation. Each of these fuctios must (1) be no longer than six statements, and (2) not employ (or simulate) iteration or recursion over bit positions:
  //- unsigned long set_bits(unsigned nSet) which returns an integer whose nset least significant bits are set (the rest are zero)
  //- unsigned long set_range(unsigned nSet, unsigned lsb) which returns an integer whose lsb least significant bits are zero, and the successive nset bits are one
  //- unsigned long invert_range(unsigned long val, unsigned nSet, unsigned lsb) which selectively inverts nset bits in val starting at bit lsb and returns that value
  //Hint: your implementation of invert_range may utilize set_range and set_range may utilize set_bits as helper functions.

#include <stdio.h>

unsigned long set_bits(unsigned long nSet) {
  //this method will return an integer whose nset lsb (right) are set (and the rest are zero)
  //knowing that shifting an unsigned integer will insert 0s, initialize my value to 1s
  unsigned long num = 0; num = ~ num;
  //now, shifting left by nSet will insert nSet 0s
  num = num << nSet;
  //inverting this result will now result in all the leading 1s being 0s, and the lsb 0s being 1s
  num = ~ num;
  return num;
}

unsigned long set_range(unsigned long nSet, unsigned int lsb) {
  //this method will return an integer whose lsbs are zero, and the next nSet bits are one
  //first, we get the nSet number, which we can call the set_bits function to do
  unsigned long num = set_bits(nSet);
  //now we shift left again to add lsb 0s in the right
  num = num << lsb;
  return num;
}

unsigned long invert_range(unsigned long val, unsigned int nSet, unsigned int lsb) {
  //this method will invert nSet bits in val, starting at bit lsb, and return the new value
  //first, we will create a temporary value which will be created with nSet 1s shifted lsb
  unsigned long tmp = set_range(nSet,lsb);
  //now, we will use the properties of bitwise exclusive-or
  val = val^tmp;  
  return val;
}

int main(void) {
  int nSet = 3;
  printf("set_bits(%i) = %u\n", nSet, set_bits(nSet));
  int lsb = 1;
  printf("set_range(%i,%i) = %u\n", nSet, lsb, set_range(nSet,lsb));
  unsigned long val = 32;
  printf("invert_range(%u,%i,%i) = %u\n", val, nSet, lsb, invert_range(val,nSet,lsb));
}
