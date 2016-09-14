all: quicksortp_test shellsortp_test
clean:
	rm -f *.o quicksortp_test* shellsortp_test

quicksortp_test: quicksortp.o quicksortp_test.o
	gcc -g -O0 -o $@ $^ -lm
quicksortp.o: quicksortp.c quicksortp.h swapp.h
	gcc -g -O0 -c quicksortp.c
quicksortp_test.o: test_driverp.c quicksortp.h
	gcc -g -O0 -c -o $@ -DSORT=quicksortp test_driverp.c

shellsortp_test: shellsortp.o shellsortp_test.o
	gcc -g -O0 -o $@ $^ -lm
shellsortp.o : shellsortp.c shellsortp.h
	gcc -g -O0 -c shellsortp.c
shellsortp_test.o: test_driverp.c shellsortp.h
	gcc -g -O0 -c -o $@ -DSORT=shellsortp test_driverp.c
