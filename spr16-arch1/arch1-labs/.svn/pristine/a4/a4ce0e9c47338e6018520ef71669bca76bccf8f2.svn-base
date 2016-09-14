#include "quicksortGoto.h"
#include "swap.h"

/* public interface for qhelper2() that sorts an array a of length len 
 *
 * @param int a[] the array to be sorted
 * @param int len the length of the array being sorted
 */
static void qhelper2(int a[], int left, int right) {
  //this static helper method implements quicksort in goto-c
  int i, last, pivot;
  if ( left<right ) goto cont;
    return;
 cont:
  swap(a[left],a[(left+right)/2]);
  pivot = a[left];
  last = left;
  i = left+1;
  goto start;
 start:
  if ( i>right ) goto end;
    if ( a[i]>=pivot ) goto again;
    last++;
    swap(a[last],a[i]);
    goto again;
    again:
      i++;
      goto start;
  end:
  swap(a[left],a[last]);
  qhelper2(a,left,last-1);
  qhelper2(a,last+1,right);
}

void quicksortGoto(int to_sort[], int len) {
  qhelper2(to_sort, 0, len-1);
}
