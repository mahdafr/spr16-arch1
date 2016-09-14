//Exercise 4-14: Define a macro swap(t,x,y) that interchanges two
//arguments of type t. (Block structure will help.)

#define swap(t,x,y) if(sizeof(t)==sizeof(x) && sizeof(t)==sizeof(y)){ t=x; x=y; y=t; }

#include <stdio.h>

int main(void) {
  //int t=5, x=4, y=3;
  //swap(t,x,y);
  //printf("t=5, x=4,y=3\nt=%d, x=%d, y=%d\n",t,x,y);

  //long t=10, x=15, y=75;
  //swap(t,x,y);
  //printf("t=10, x=15, y=75\nt=%d, x=%d, y=%d\n",t,x,y);

  int t=0, x=15;
  short y=75;
  swap(t,x,y);
  printf("t=0, x=15, y=75\nt=%d, x=%d, y=%d\n",t,x,y);
}
