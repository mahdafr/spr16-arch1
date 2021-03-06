#include <msp430g2553.h>
#include "lcd_utils.h"
#include "draw_arena.h"
#include "buttons.h"
#define P1SwMask SW1
#define P2SwMask (UpSw + DownSw + LeftSw + RightSw)
unsigned char oldP1SwVal, oldP2SwVal;

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

/* global vars */
u_char shapeY = SHAPE_START_Y_POSITION;
u_char shapeX = SHAPE_START_X_POSITION;
int timerCount = 1;
 
void resetGameState(void);	/* forward definition */

void updateShape();

void main(void) {  
  WDTCTL = WDTPW + WDTHOLD;     // Stop watchdog timer

  lcdinit();                    // init LCD (also: CPU clock to 16MHz)
  lcd_setAddr(0,3);

  CCTL0 = 0; //CCIE;                 // CCR0 interrupt enabled
  TACTL = TASSEL_2 + MC_1 + ID_3; // Set timer clock to CPU clock/8
  CCR0 = 50000;			// Interrupt every 10 ms

  initializeSwitchInterrupts();
  resetGameState();
  or_sr(0x18);			// CPU off, GIE on
}  

/* Switches on P1 (far right switch) */
interrupt(PORT1_VECTOR) Port_1(void) {
  unsigned char p1Val = P1IN & P1SwMask; /* read switches from p1 */
  P1IES= p1Val;			/* interrupt on value change */
  P1IFG = 0;			/* clear pending P1 interrupts  */

  // reset everyting on press of SW1 (on right)
  if (!(p1Val & SW1) && (oldP1SwVal & SW1)) /* transition from unpressed to pressed? */
    resetGameState();			   /* re-initialize paddle */
  oldP1SwVal = p1Val;
}

/* Switches on P2 (direction pad) */
interrupt(PORT2_VECTOR) Port_2(void) {
  unsigned char p2Val = P2IN & P2SwMask; /* read switches from p2 */
  P2IES= p2Val;			/* interrupt on value change */
  P2IFG = 0;			/* clear pending P2 interrupts  */
  /* just remember button state */
  oldP2SwVal = p2Val;
  /* toggle the timer interrupt when the button is pressed */
  CCTL0 ^= CCIE;
  timerCount = 1;
  updateShape();
}


void updateShape(void) {	/* called by timer interrupt handler */
  // check if up switch is pressed
  //LCD: upper bound = 0 and lower bound = 68
  if (!(oldP2SwVal & UpSw))  {
    if (shapeY >= 5) { //originally 8
      shapeY -= 1; //originally 2
    }
  }
  // check if down switch is pressed
  if (!(oldP2SwVal & DownSw))  {
    if (shapeY < 61) { //oroginally 56
      shapeY += 1; //originally 2
    }
  }
  // check if up switch is pressed
  //LCD: left boundary = 0 and right boundary = 96
  if (!(oldP2SwVal & LeftSw))  {
    if (shapeX > 5) { //originally 2
      shapeX -= 1; //originally 2
    }
  }
  // check if down switch is pressed
  if (!(oldP2SwVal & RightSw))  {
    if (shapeX < 93) { //originally 94
      shapeX += 1; //originally 4
    }
  }
  updateCursor(shapeX, shapeY);     
}

/* timer interrupt */
interrupt(TIMER0_A0_VECTOR) Timer_0(void) {
  // if timerCount is zero update shape
  if (!timerCount) {
    updateShape();
  }

  // update count
  timerCount++;

  // reset every 10
  if (10 == timerCount) {
    timerCount = 0;
  }
}

  
void resetGameState(void) {
  shapeY = SHAPE_START_Y_POSITION;
  shapeX = SHAPE_START_X_POSITION;

  drawArena();
  updateCursor(shapeX, shapeY);
  //drawArena();
}
