# Demo Makefile for lab 2-2.  
#
# @author Adrian Veliz
# @author Eric Freudenthal
# @version 0.1.20130910
#


# makfile configuration
COMMON_OBJECTS	= interrupts.o sr.o
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} 

#switch the compiler (for the internal make rules)
CC              = msp430-gcc
AS              = msp430-as

all: flash.elf 

#additional rules for files
flash.elf: ${COMMON_OBJECTS} flashMain.o stateMachines.o
	${CC} ${CFLAGS} -o $@ $^

install: flash.elf
	mspdebug rf2500 "prog flash.elf"

clean:
	rm -f *.o *.elf


#project dependencies
flashMain.o: flashMain.c

stateMachines.o: stateMachines.c

interrupts.o: interrupts.s

sr.o: sr.s
