#include <msp430.h>

//state machine
#define waitForUp 0
#define waitForDn 1

/*
 * @author: Mahdokht Afravi
 * @modified: 04/07 R
 * this is my program for part3 of lab2-2
 */

unsigned char buttonState = waitForDn; //start in state 1
static unsigned char iter = 0;
static unsigned char green = 0;
unsigned char red = 0;

void pushControl(void);
void timerHandler(void);
void flashControl(void);

void btnHandler() {
  //this method works with led_ctrlPush() for button press
  //called when interrupt occurs
  if ( buttonState == waitForUp ) {
    buttonState = waitForDn;
    //interrupt sensitive to button down
    P1IES |= BIT3;
  } else {
    //button is up
    buttonState = waitForUp;
    //interrupt sensitive to button up
    P1IES &= ~BIT3;
  }
  //clear interrupt
  P1IFG &= ~BIT3;
  pushControl();
}

void pushControl() {
  //works with btnHandler() for button press
  char flag = 0;
  switch ( buttonState ) {
  case waitForUp:
    red = 1 - red;
    //if it was on, turn off
    if ( red ) flag &= ~BIT0;
    //if it was off, turn on
    else flag |= BIT0;
    break;
  case waitForDn:
    //if red was on, leave it on
    if ( red ) flag |= BIT0;
    //if red was off, leave it off
    else flag &= ~BIT0;
    break;
  }
  //clear bits for off LEDs
  P1OUT &= (0xff-(BIT0+BIT6)) | flag;
  //set bits for on LEDs: stored in switch cases
  P1OUT |= flag;
}

void timerHandler() {
  //this method controls the flashing of the green led
  //with counter: 4Hz if red is on and 1Hz if red is off
  iter++;
  if ( red && iter>=100 ) {
    green = 1 - green;
    iter = 0;
  }
  if ( red==0 && iter>=25 ) {
    green = 1 - green;
    iter = 0;
  }
  //green = 1; //testing to see WHY GREEN WILL NOT TURN ON?!
  flashControl();
  //P1OUT = BIT6; //testing to see WHY GREEN WILL NOT TURN ON?!
}

void flashControl() {
  //this method controls the flashing of the green led
  char flag = 0;
  //turn on the green if we should
  if ( green )
    flag |= BIT6;
  //turn off the green if we should
  else
    flag &= ~BIT6;
  //clear bits for off LEDs
  P1OUT &= (0xff-(BIT0+BIT6)) | flag;
  //set bits for on LEDs: stored in switch cases
  P1OUT |= flag; //BIT6; //testing to see WHY GREEN WILL NOT TURN ON?!
}
