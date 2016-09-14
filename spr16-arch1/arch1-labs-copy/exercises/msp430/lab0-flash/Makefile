#
# Makefile - blink.elf
#
# @author Adrian Veliz
# @author Eric Freudenthal
# @version 0.1.20130815
#


# makfile configuration
COMMON_OBJECTS	= blink.o config_clocks.o #variable to store the object files
SLEEP_OBJECTS	= sleep_600th.o sleep_sec_c.o
CPU             = msp430g2553 #utilizing this hardware: which model we are working with
CFLAGS          = -mmcu=${CPU} #targets the microcontroller cpu

# switch the compiler (for the internal make rules)
CC              = msp430-gcc #compiling code to work with the msp430
AS              = msp430-as #compiles the assembly code

all: blink_c.elf blink_s.elf

#additional rules for files
blink_c.elf: ${COMMON_OBJECTS} ${SLEEP_OBJECTS} led_c.o #the executable linkable format that is built from install_c command, using the common_objects variables
	${CC} ${CFLAGS} -o $@ $^
#this instruction installs the built code to work with the msp430
install_c: blink_c.elf
	mspdebug rf2500 "prog blink_c.elf" #message output for error
#this cleans the object files and elf files which will not be needed to execute on hardware
clean:
	rm -f *.o *.elf

#project dependencies
blink.o: blink.c #main function

config_clocks_.o: config_clocks_.c #sets the frequency of the msp430's clock to 1MHz

sleep_sec_c.o: sleep_sec_c.c #sets the sleep cycle for the msp430

sleep_600th.o: sleep_600th.s #sets to loop for 1/600-th of a second

led_c.o: led_c.c #controls whether led is on or off

#the make command for part2
blink_s.elf: ${COMMON_OBJECTS} ${SLEEP_OBJECTS} led_s.o
	${CC} ${CFLAGS} -o $@ $^ #here is where I tried to utilize the AS to build the elf
install_s: blink_s.elf
	mspdebug rf2500 "prog blink_s.elf"
led_s.o: led_s.s

#the make commands for part3
all: blink_c.elf blink_s.elf

#additional rules for files
blink_d.elf: ${SLEEP_OBJECTS} dimmer.o led_c.o config_clocks.o #the executable linkable format that is built from install_c command, using the common_objects variables
	${CC} ${CFLAGS} -o $@ $^
dimmer.o : dimmer.c
#this instruction installs the built code to work with the msp430
install_d: blink_d.elf
	mspdebug rf2500 "prog blink_d.elf" #message output for error
