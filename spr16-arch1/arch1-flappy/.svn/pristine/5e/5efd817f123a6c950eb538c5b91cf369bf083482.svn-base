#
# Makefile - timer.elf
#
# @author Adrian Veliz
# @author Eric Freudenthal
# @version 0.1.20130910
#

# IMPORTANT: There are multiple variants of the LCD_1202 board.
# To function correctly, be sure to define LCD_1202 to the board's version number.
#
# The file "paddleButtons.h" depends upon the value of the macro "LCD1202_VERSION."
#
# The version number is printed on the upper right corner of the boards 
# beneath the words "Nokia 1202"
# If no version is indicated, then your board is version "v1".
#
# This Makefile requires that the LCD1202_VERSION variable be specified by the parameter.  
#    LCD1202_VERSION=N
# Where N is replaced by the version number.
#
# For example, the following command will build all targets for board "v1"
#    $ make all LCD1202_VERSION=1
#

all: install_pipes install_score

# makfile configuration
COMMON_OBJECTS  =
LIBRARY_FILE	= ../lib/libmsp.a
CPU             = msp430g2553 
CFLAGS          = -DLCD1202_VERSION=$(LCD1202_VERSION) -I../include -mmcu=${CPU} -Os -g 

#switch the compiler (for the internal make rules)
CC              = msp430-gcc
AS              = msp430-as

#additional rules for files

install_pipes: draw_pipe.elf
	mspdebug rf2500 "prog $^"
draw_pipe.elf: draw_pipe.o pipe_demo.o draw_bird.o ${LIBRARY_FILE}
	msp430-gcc ${CFLAGS} -o $@ $^

install_score: draw_score.elf
	mspdebug rf2500 "prog $^"
draw_score.elf: score_demo.o ${LIBRARY_FILE}
	msp430-gcc ${CFLAGS} -o $@ $^

clean:
	rm -f *.o *.elf
