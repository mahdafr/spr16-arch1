# Mahdokht Afravi, 80483123
# CS 3432 Arch1, Lab2-1
# Last Modified: 03.28 M

CPU = msp430g2553
CFLAGS = -mmcu=${CPU}
CC = msp430-gcc
AS = msp430-as

all: load_c load_s
# compile led_press.c to a loadable elf file (default production)
toggle_c.elf: led_press.o transition_c.o debounce.o
	${CC} ${CFLAGS} -o $@ $^
# load elf file onto launchpad
load_c: toggle_c.elf
	mspdebug rf2500 "prog toggle_c.elf"
# for part4, compile the assembly file
toggle_s.elf: led_press.o transition_s.o debounce.o
	${CC} ${CFLAGS} -o $@ $^
load_s: toggle_s.elf
	mspdebug rf2500 "prog toggle_s.elf"

# removing all files created from compilation
clean:
	rm -f *.o *.elf

# object file for main function
led_press.o: led_press.c
# compile transition_c: update_state()
transition_c.o: transition_c.c
# object file for part3: debounce
debounce.o: debounce.c
# object file for part4: assembly
transition_s.o: transition_s.s
