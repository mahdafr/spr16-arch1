#include "msp430.h"
#include "debounce.h"
#include "transition_c.h"

//   @author: Mahdokht Afravi, 80483123
//   @modified: 03.31 R

static unsigned char state = 0;

void update_state() {
  switch ( state ) {
  //if we are starting, everything is off
  case 0:
    //everything is off
    P1OUT &= ~BIT6; //green off
    P1OUT |= BIT0; //red on
    //we use the following line for part2 of lab2-1
    while ( !(P1IN & BIT3) ) ; //stay in this state
    debounce();
    state++;
    break;
    //if we are in the first state
  case 1:
    //red is on, green is off
    P1OUT &= ~BIT0; //red off
    P1OUT |= BIT6; //green on
    //we use the following line for part2 of lab2-1
    while ( !(P1IN & BIT3) ) ; //stay in this state
    debounce();
    state = 0;
    break;
  }
}
