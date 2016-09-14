#include <msp430.h>

// for flashRED state machine
//static unsigned char ledState = 0; /* boolean: true = red led on */
static unsigned char count = 0;
static unsigned char green = 0;
static unsigned char red = 0;
void led_control();

void timerHandler() {
  count++;
  if ( count>=100 ) {
    green = 1-green;
    count = 0;
  }
  if( count%25 == 0 )
    red = 1 - red;
  led_control();
}

void led_control() {	     /* not a state machine: set LEDs from state variables */
  char flag = 0;
  if (green == 1)
    flag |= BIT0;
  if(red == 1)
    flag |= BIT6;
  P1OUT &= (0xff-(BIT6+BIT0)) | flag; // clear bit for off leds
  P1OUT |= flag;		      // set bit for on leds
}
