#include <msp430g2553.h>
#include "lcd_utils.h"
#include "drawPipe.h"

#include "paddleButtons.h"	/* direction button bits */
#define P1SwMask SW1
#define P2SwMask (UpSw + DownSw + LeftSw + RightSw)
unsigned char oldP1SwVal, oldP2SwVal; /* current switch values */

/* global vars */
short pipeXPos = 48; //10;
short pipeYPos = 34; //10;
short pipeXVel = 1; //originally: 1
short pipeYVel = 1; //originally: 1

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

updatePipe() {
  /* reverse ball direction at court boundaries */
  if ((pipeXPos == 0) || (pipeXPos == MAX_X -2)) 
    pipeXVel = -pipeXVel;
  if ((pipeYPos == 0) || (pipeYPos == MAX_Y -2))
    pipeYVel = -pipeYVel;
  /* move pipe */
  pipeXPos += pipeXVel;
  pipeYPos += pipeYVel;  
  /* draw pipe */
  drawPipe(pipeXPos, pipeYPos);
}

/* timer interrupt */
interrupt(TIMER0_A0_VECTOR) Timer_0(void) {
  static int clockDivide = 0;
  if (clockDivide++ > 20) {
    updatePipe();
    clockDivide = 0;
  }
}

void resetPipe(void) {
  pipeXPos = 48; //10;
  pipeYPos = 34; //30;
  pipeXVel = 1;
  pipeYVel = 1;
  drawPipe(pipeXPos,pipeYPos);
}
