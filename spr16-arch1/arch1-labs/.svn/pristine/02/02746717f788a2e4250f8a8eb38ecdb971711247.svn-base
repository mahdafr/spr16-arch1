all: quicksort_test exc4-14 shellsort_test quicksortGoto_test
clean:
	rm -f *.o quicksort_test*
	rm exc4-14
	rm shellsort_test
	rm quicksortGoto_test

exc4-14: exc4-14.c
	gcc -o exc4-14 exc4-14.c

shellsort_test: shellsort.o shellsort_test.o
	gcc -g -o $@ $^ -lm
shellsort.o : shellsort.o shellsort_test.o
	gcc -g -c shellsort.c
shellsort_test.o: test_driver.c shellsort.h
	gcc -g -c -o $@ -DSORT=shellsort test_driver.c

quicksortGoto_test: quicksortGoto.o quicksortGoto_test.o
	gcc -g -o $@ $^ -lm
quicksortGoto.o : quicksortGoto.o quicksortGoto_test.o
	gcc -g -c quicksortGoto.c
quicksortGoto_test.o: test_driver.c quicksortGoto.h
	gcc -g -c -o $@ -DSORT=quicksortGoto test_driver.c

quicksort_test: quicksort.o quicksort_test.o
	gcc -g -o $@ $^ -lm

quicksort.o: quicksort.c quicksort.h swap.h
	gcc -g -c quicksort.c

quicksort_test.o: test_driver.c quicksort.h
	gcc -g -c -o $@ -DSORT=quicksort test_driver.c
