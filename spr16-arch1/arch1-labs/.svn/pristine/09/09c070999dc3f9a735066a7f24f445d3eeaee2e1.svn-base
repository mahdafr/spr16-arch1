#include <stdio.h>
#include <limits.h>

/* 
 *  SORT test program
 *  should be compiled with -DSORT=sortname
 *  where:
 *    sortname() is a sorting function with signature void sortname(int a[], int len)
 *    sortname.h is the name of a header file where the signature of sortname() is declared.
 */

/* 
 *   macros for converting SORTNAME into a character string
 *
 *  Big ideas:
 *    #string expands to "string", but won't expand string if it's a macro
 *    SORT is itself a macro that needs to be expanded, so #SORT won't work
 *  How it works: 
 *    str(s) expands the definition of SORT to the sortname
 *    _str(s) quotes the resulting string 
 */
#define str(s) _str(s)		/* make string constant */
#define _str(s) #s		/* helper */

/* include sortname.h -- note use of str macro */
#include str(SORT.h)		

/* Length of array to test */
#define LENGTH 100000

/*
 * Main test driver program
 */

int main()
{
  int a[LENGTH], i;
  for (i = 0; i < LENGTH; i++)	/* fill a with random integer values */
    a[i] = random();
  SORT(a, LENGTH);
  for (i = 1; i < LENGTH; i++)	/* confirm that a is sorted */
    if (a[i-1] > a[i]) {
      fprintf(stderr, "array mis-sorted by %s()\n", str(SORT));
      return -1;
    }
  printf("%s() worked correctly\n", str(SORT));
  return 0;
}
