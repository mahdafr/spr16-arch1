all: namesBST

namesBST.o: namesBST.h namesBST.c
	gcc namesBST.c -c -g -o namesBST.o
namesBST: namesBST.o
	gcc namesBST.o -o namesBST
clean:
	rm -f namesBST *.o
