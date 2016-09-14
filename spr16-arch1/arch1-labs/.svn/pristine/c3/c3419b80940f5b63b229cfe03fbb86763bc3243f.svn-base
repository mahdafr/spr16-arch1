#include <msp430g2553.h>
#include "lcd_utils.h"
#include "drawPipe.h"
#include "paddleButtons.h"	/* direction button bits */

#define P1SwMask SW1
#define P2SwMask (UpSw + DownSw + LeftSw + RightSw)

unsigned char oldP1SwVal, oldP2SwVal; /* current switch values */

/* global vars */
short pipeXPos = MAX_X;
short pipeXVel = -1;
short gapHeight = 15;
short gapTop = MAX_Y/2;

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

void resetPipe();
void newGapTop();
void newGapHeight();

void main(void) {
  WDTCTL = WDTPW + WDTHOLD;     // Stop watchdog timer
  lcdinit();                    // init LCD (also: CPU clock to 16MHz)
  CCTL0 = CCIE;                 // CCR0 interrupt enabled
  TACTL = TASSEL_2 + MC_1 + ID_3; // Set timer clock to CPU clock/8
  CCR0 = 50000;			// Interrupt every 10 ms
  initializeSwitchInterrupts();	// switch interrupts
  resetPipe();
  or_sr(0x18);			// CPU off, GIE on
} 

/* Switches on P1 (far right switch) */
interrupt(PORT1_VECTOR) Port_1(void) {
  unsigned char p1Val = P1IN & P1SwMask; /* read switches from p1 */
  P1IES= p1Val;			/* interrupt on value change */
  P1IFG = 0;			/* clear pending P1 interrupts  */
  if (!(p1Val & SW1) && (oldP1SwVal & SW1)) /* transition from unpressed to pressed? */
    resetPipe();			   /* re-initialize paddle */
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

updatePipe(u_char gap) {
  // when pipe reaches left edge, reset to far right
  if ( pipeXPos <= 0 )
    pipeXPos = MAX_X;
  //move pipe left: vel is negative
  pipeXPos += pipeXVel;
  //draw pipe
  newGapTop();
  drawPipe(pipeXPos, gapHeight, gapTop);
}
void newGapTop() {
  //some kind of "random" generator...
  if ( gapTop >= MAX_Y-20 || gapTop <= 20 )
    gapTop = 15;
  else
    gapTop += (gapTop - 5);
}

/* timer interrupt */
interrupt(TIMER0_A0_VECTOR) Timer_0(void) {
  static int clockDivide = 0;
  if (clockDivide++ > 20) {
    clockDivide = 0;
    //newGapHeight();
    updatePipe(gapHeight);
  }
}
void newGapHeight() {
  //some kind of "random" generator...
  if ( gapHeight >= 20 )
    gapHeight -= gapHeight+5;
  else
    gapHeight += gapHeight-5;
}

void resetPipe(void) {
  pipeXPos = MAX_X;
  pipeXVel = -1;
  gapHeight = 15;
  drawPipe(pipeXPos,gapHeight,gapTop);
}
