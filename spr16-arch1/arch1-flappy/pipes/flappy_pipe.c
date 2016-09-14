#include <msp430g2553.h>
#include "lcd_utils.h"
#include "drawPipe.h"
#include "paddleButtons.h"	/* direction button bits */

#define P1SwMask SW1
#define P2SwMask (UpSw + DownSw + LeftSw + RightSw)

unsigned char oldP1SwVal, oldP2SwVal; /* current switch values */
//the set of the pipes, maximum 6 on the screen
short pipePos[6]; //saving each pipe's current X position
short pipeGapTop[6]; //saving each pipe's top boundary of the gap
short pipeGapHeight[6]; //saving each pipe's gap height
//which pipe?
short pipe = 0;
//default position, velocity, gapTop and gapHeight
short pipeXPos = 6; //starting from far right
short pipeVel = -1; //moving slowly at first
short gapTop = MAX_Y/2; //row gap begins
short gapHeight = 15; //rows in gap

/* setup switch interrupts */
void initializeSwitchInterrupts() {
  P1REN |= P1SwMask;		/* resistors for switches */
  P2REN |= P2SwMask;
  P1OUT |= P1SwMask;		/* pull-ups for switches */
  P2OUT |= P2SwMask;
  oldP1SwVal = P1IN & P1SwMask;	/* remember current switch vales */
  oldP2SwVal = P2IN & P2SwMask;
  P1IES = oldP1SwVal;		/* interrupt when switch bits change */
  P2IES = oldP2SwVal;
  P1IE = P1SwMask;		/* enable interrupts from switches */
  P2IE = P2SwMask;
}

void resetPipes();
void newGapTop();
void newGapHeight();
void updateAllPipes();

void main(void) {
  WDTCTL = WDTPW + WDTHOLD;     // Stop watchdog timer
  lcdinit();                    // init LCD (also: CPU clock to 16MHz)
  CCTL0 = CCIE;                 // CCR0 interrupt enabled
  TACTL = TASSEL_2 + MC_1 + ID_3; // Set timer clock to CPU clock/8
  CCR0 = 50000;			// Interrupt every 10 ms
  initializeSwitchInterrupts();	// switch interrupts
  resetPipes();
  or_sr(0x18);			// CPU off, GIE on
}

/* Switches on P1 (far right switch) */
interrupt(PORT1_VECTOR) Port_1(void) {
  unsigned char p1Val = P1IN & P1SwMask; /* read switches from p1 */
  P1IES = p1Val;		/* interrupt on value change */
  P1IFG = 0;			/* clear pending P1 interrupts  */
  if (!(p1Val & SW1) && (oldP1SwVal & SW1)) /* transition from unpressed to pressed? */
    resetPipes();			   /* re-initialize paddle */
  oldP1SwVal = p1Val;
}

/* Switches on P2 (direction pad) */
interrupt(PORT2_VECTOR) Port_2(void) {
  unsigned char p2Val = P2IN & P2SwMask; /* read switches from p2 */
  P2IES= p2Val;			/* interrupt on value change */
  P2IFG = 0;			/* clear pending P2 interrupts  */
  /* just remember button state */
  oldP2SwVal = p2Val;
}

void updateAllPipes() {
  for ( pipe=0 ; pipe<6 ; pipe++ ) {
    //draw all six pipes at different X positions
    pipePos[pipe] = (pipeXPos-=6);
    pipeGapTop[pipe] = gapTop;
    //randomize gapTop
    //newGapTop();
    pipeGapHeight[pipe] = gapHeight;
    //newGapHeight();
    //drawPipe(pipePos[pipe],pipeGapHeight[pipe],pipeGapTop[pipe]);
    updatePipe();
  }
  if ( pipePos[0]<=0 ) {
    short j;
    for ( j=1 ; j<pipe ; j++ ) {
      pipePos[j-1] = pipePos[j];
      pipeGapTop[j-1] = pipeGapTop[j];
      pipeGapHeight[j-1] = pipeGapHeight[j];
    }
  }
}

updatePipe() {
  // when pipe reaches left edge, reset to far right
  //if ( pipeXPos <= 0 )
    //pipeXPos = MAX_X;
  //move pipe left: vel is negative
  pipeXPos += pipeVel;
  //draw pipe with same gapHeight and gapTop unchanged
  pipePos[pipe] = pipeXPos;
  drawPipe(pipePos[pipe], pipeGapHeight[pipe], pipeGapTop[pipe]);
}

void newGapTop() {
  //some kind of "random" generator...
  if ( gapTop >= MAX_Y-20 || gapTop <= 20 )
    gapTop = 15;
  else
    gapTop += (gapTop - 5);
}
void newGapHeight() {
  //some kind of "random" generator...
  if ( gapHeight >= 20 )
    gapHeight -= gapHeight+5;
  else
    gapHeight += gapHeight-5;
}

/* timer interrupt */
interrupt(TIMER0_A0_VECTOR) Timer_0(void) {
  static int clockDivide = 0;
  if ( clockDivide++ > 20 ) {
    clockDivide = 0;
    //updateAllPipes();
  }
}

void resetPipes(void) {
  pipeXPos = MAX_X;
  pipeVel = -1;
  gapTop = 25;
  gapHeight = 15;
  for ( pipe=0 ; pipe<6 ; pipe++ ) {
    //draw all six pipes at different X positions
    pipePos[pipe] = (pipeXPos-6);
    pipeXPos -= 6;
    //randomize gapTop and gapHeight
    pipeGapTop[pipe] = gapTop;
    newGapTop();
    pipeGapHeight[pipe] = gapHeight;
    //newGapHeight();
    drawPipe(pipePos[pipe],pipeGapHeight[pipe],pipeGapTop[pipe]);
    //updatePipe();
  }
  pipeXPos = MAX_X;
  pipeVel = -1;
  gapTop = 25;
  gapHeight = 15;
  pipe = 0;
}
