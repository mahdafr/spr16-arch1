# Makefile to create archive for MSP430 components
# makefile configuration
OBJECTS  = lcd_backend.o lcd_utils.o sr.o lcd_char.o string_utils.o 
LIBS	 = libmsp.a
LIBRARY_PATH = ../lib/

CPU             = msp430g2553 
CFLAGS          = -mmcu=${CPU} -I../include -Os -g 

#switch the compiler (for the internal make rules)
CC              = msp430-gcc
AS              = msp430-as
AR		= msp430-ar

all: ${LIBS}

${LIBS}: ${OBJECTS}
	${AR} crs $@ ${OBJECTS}

install: ${LIBS}
	cp *.h ../include/
	mv libmsp.a ${LIBRARY_PATH}

clean:
	rm -rf *.o ${LIBRARY_PATH}${LIBS} ../include/*.h
