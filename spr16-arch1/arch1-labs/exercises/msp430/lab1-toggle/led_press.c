#include "msp430.h"
#include "transition_c.h"
//#include "debounce.h"

void configureClocks();
//static unsigned char state = 0;
//the method for part 2
//void update_state();

void main(void) {
  WDTCTL = WDTPW + WDTHOLD;  //Disable watchdog timer
  configureClocks();
  P1DIR = BIT0 + BIT6; 		/* LED bits are for output */
  // Configure Switch on P1.3 //
  P1REN |= BIT3;		// Resistor ENable for switch (P1.3)
  P1OUT =  BIT3 + BIT0;	// Send 1 to switch, red LED on
  
  while (1) {
    //mask all but the button: bit3 ON = 0x08
    if( !(P1IN & BIT3) ) {
      //P1OUT = BIT6+BIT3;	/* Switch 1 + green */
      //or
      //P1OUT &= ~BIT0;		//turn off red
      //P1OUT |= BIT6;		//turn on green
      update_state();
    } else {
      //P1OUT = BIT0 + BIT3;    /* Switch 1 + red */
      //or
      //P1OUT &= ~BIT6;         //turn off green
      //P1OUT |= BIT0;          //turn red on
    }
  }
}

void configureClocks() {
  // Set system DCO to 1MHz
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL = CALDCO_1MHZ;
  // Set LFXT1 to the VLO @ 12kHz
  BCSCTL3 |= LFXT1S_2;
}
/*
void update_state() {
  switch ( state ) {
  //if we are in the first state
  case 0:
    //red is on, green is off
    P1OUT &= ~BIT6;             //turn off green
    P1OUT |= BIT0;              //turn on red
    while ( !(P1IN & BIT3) ) ; //stay
    state++;
    break;
  //if we are in the second state
  case 1:
    //red is off, green is on
    P1OUT &= ~BIT0;		//turn off red
    P1OUT |= BIT6;		//turn on green
    while ( !(P1IN & BIT3) ) ; //stay
    state = 0;
    break;
  }
  }*/
