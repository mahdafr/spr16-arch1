# Demo Makefile for lab 2-2.  
#
# @author Adrian Veliz
# @author Eric Freudenthal
# @version 0.1.20130910
#


# makfile configuration
COMMON_OBJECTS  = interrupts.o sr.o main.o
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} 

#switch the compiler (for the internal make rules)
CC              = msp430-gcc
AS              = msp430-as

all: c-combined.elf

#additional rules for files
c-combined.elf: ${COMMON_OBJECTS} c-combined.o
	${CC} ${CFLAGS} -o $@ $^
install: c-combined.elf
	mspdebug rf2500 "prog c-combined.elf"

clean:
	rm -f *.o *.elf


#project dependencies
main.o: main.c

interrupts.o: interrupts.s
sr.o: sr.s

c-combined.o: c-combined.c
