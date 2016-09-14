#include "quicksort.h"
#include "swap.h"

/* 
 * helper fuction that actually implements quicksort
 * a[left] through a[right] is recursively sorted
 *
 * @param int to_sort[] the array being sorted
 * @param int left the lower bound of range being sorted
 * @param int right the higher bound of range being sorted
 */
static void qhelper(int to_sort[], int left, int right)
{
  int i, last, pivot;
  if (left >= right)		// array range smaller than 0 
    return;			// nothing to sort
  swap(to_sort[left], to_sort[(left+right)/2]); // pivot into a[left]
  pivot = to_sort[left];
  last = left; // last+1 is first destination for swaps of vals<pivot
  for (i = left+1; i <= right; i++) // i scans elements after pivot
    if (to_sort[i] < pivot) {		    //swap vals < pivot to indexes starting from last+1
      last++;
      swap (to_sort[last], to_sort[i]);
    }
  swap(to_sort[left], to_sort[last]);	// put pivot where it belongs
  // recursively sort lef and right sub-ranges
  qhelper(to_sort, left, last-1); qhelper(to_sort, last+1, right); 
}

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

void quicksort(int to_sort[], int len) 
{
  //qhelper2 is the goto-c of qhelper
  qhelper2(to_sort, 0, len-1);
}
