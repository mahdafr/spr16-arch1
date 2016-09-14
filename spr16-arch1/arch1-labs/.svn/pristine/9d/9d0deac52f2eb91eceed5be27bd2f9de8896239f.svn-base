all: calendar_test
clean: 
	rm -f *.o calendar_test

calendar_test: calendar_utils.o calendar_test.o
	gcc -g -O0 -o $@ $^ -lm

calendar_utils.o: calendar_utils.c calendar_utils.h
	gcc -g -O0 -c calendar_utils.c

calendar_test.o: calendar_test.c calendar_utils.h
	gcc -g -O0 -c -o $@ calendar_test.c
