#include "quicksortp.h"
#include "swapp.h"

/* public interface for quicksort 
 *
 * @param int to_sort[] the array to be sorted
 * @param int len the length of the array being sorted
 */
void quicksortp(int **p, int len)
{
  int right = len-1;
  int **to_sort = p;
  int i, last, pivot;
  if (len <= 1)			/* one or less items to sort */
    return;			/* nothing to sort */
  swapp(*to_sort, *(to_sort+(right/2))); /* pivot into a[0] */
  pivot = **to_sort;
  last = 0; /* last+1 is first destionation for swaps of vals<pivot */
  for (i = 1; i <= right; i++) /* i scans elements after pivot */
    if (**(to_sort+i) < pivot) { /* swap vals < pivot to indexes starting from last+1 */
      last++;
      swapp(*(to_sort+last), *(to_sort+i));
    }
  swapp(*to_sort, *(to_sort+last));	/* put pivot where it belongs */
  /* recursively sort left and right sub-ranges */
  quicksortp(p, last); 
  quicksortp(p+last+1, len-(last+1));
}


