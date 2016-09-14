#include "debounce.h"

void debounce() {
  //since the fetch instructions for this
    //method is 4 cycles, we will run for
    //25000
  int cyc = 25000;
  while ( cyc!=0 ) {
    //decrementing by 4cycles...
    cyc--;
    cyc--;
  }
}
