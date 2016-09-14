#include <msp430.h>

// P1 connections:
//    P1.0 red led (1 = 0N)
//	P1.3 button (zero if down, needs resistor pull up)
//	P1.6 green led (1=ON)

void mcOsc1MHz(void) {
  //set master clock to 1MHz
  BCSCTL1 = CALBC1_1MHZ; //set range
  DCOCTL = CALDCO_1MHZ;
  BCSCTL2 &= ~(DIVS_3); //SMCLK = DCO / 8 = 1MHz
}

void main(void) {  
  WDTCTL = WDTPW + WDTHOLD;	// Stop watchdog timer
  //both: a-buttonInterrupt AND b-flash
  P1DIR = BIT0 + BIT6;	   	// bits attached to leds are output

  //a-buttonInterrupt
  P1REN = BIT3;			// enable resistor for switch
  P1OUT = BIT3;          	// pull up resistor for switch, red led on

  P1IE = BIT3;		   	// switch interrupt (bit 3) enabled
  P1IES = BIT3;		 	// switch interrupt high-low transition (wait for down)
  P1IFG &= ~BIT3;	   	// switch interrupt pending flag cleared
  or_sr(BIT5|BIT4|BIT3);	// OSC off (5) CPU off (4) , GIE (3)

  //b-flash
  mcOsc1MHz();                  // set master clock to 1MHz
  CCTL0 = CCIE;                 // Timer A interrupt enabled
  //Timer A control: Timer clock source 2: system clock
  TACTL = TASSEL_2 + MC_1;      // Mode Control 1: continuously 0...CCR0
  CCR0 = 10000;                 // Interrupt every 10,000 cycles (1MHz/10,000)

  P1DIR = BIT0 + BIT6;
  or_sr(0x18);                  // CPU off, GIE on
}


