# Demo Makefile for lab 2-2.  
#
# @author Adrian Veliz
# @author Eric Freudenthal
# @version 0.1.20130910
#


# makfile configuration
COMMON_OBJECTS  = interrupts.o sr.o
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} 

#switch the compiler (for the internal make rules)
CC              = msp430-gcc
AS              = msp430-as

all: a-button.elf a-button2.elf

#additional rules for files
a-button.elf: ${COMMON_OBJECTS} buttonIOA.o buttonMain.o
	${CC} ${CFLAGS} -o $@ $^
a-button2.elf:${COMMON_OBJECTS} buttonIOA2.o buttonMain.o
	${CC} ${CFLAGS} -o $@ $^

install: a-button.elf
	mspdebug rf2500 "prog a-button.elf"
install2: a-button2.elf
	mspdebug rf2500 "prog a-button2.elf"

clean:
	rm -f *.o *.elf


#project dependencies
buttonMain.o: buttonMain.c

buttonIOA.o: buttonIOA.c

interrupts.o: interrupts.s

sr.o: sr.s

buttonIOA2.o: buttonIOA2.c
