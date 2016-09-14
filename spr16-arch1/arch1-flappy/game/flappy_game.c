#include <msp430g2553.h>
#include "lcd_utils.h"
#include "drawBird.h"
#include "drawPipe.h"
#include "paddleButtons.h"      /* direction button bits */

#define P1SwMask SW1
#define P2SwMask (UpSw + DownSw + LeftSw + RightSw)
unsigned char oldP1SwVal, oldP2SwVal; /* current switch values */
u_char pipe = 30;

/* global vars */
short birdXPos = MAX_X/2; //1;
short birdYPos = 1;
short birdXVel = 10;
short birdYVel = 10;

/* setup switch interrupts */
void initializeSwitchInterrupts()
{
  P1REN |= P1SwMask;            /* resistors for switches */
  P2REN |= P2SwMask;
  P1OUT |= P1SwMask;            /* pull-ups for switches */
  P2OUT |= P2SwMask;
  oldP1SwVal = P1IN & P1SwMask; /* remember current switch vales */
  oldP2SwVal = P2IN & P2SwMask;
  P1IES = oldP1SwVal;           /* interrupt when switch bits change */
  P2IES = oldP2SwVal;
  P1IE = P1SwMask;              /* enable interrupts from switches */
  P2IE = P2SwMask;
}

void resetBird();
void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;     // Stop watchdog timer
  lcdinit();                    // init LCD (also: CPU clock to 16MHz)
  CCTL0 = CCIE;                 // CCR0 interrupt enabled
  TACTL = TASSEL_2 + MC_1 + ID_3; // Set timer clock to CPU clock/8
  CCR0 = 50000;                 // Interrupt every 10 ms
  initializeSwitchInterrupts(); // switch interrupts
  resetBird();
  or_sr(0x18);                  // CPU off, GIE on
}

/* Switches on P1 (far right switch) */
interrupt(PORT1_VECTOR) Port_1(void)
{
  unsigned char p1Val = P1IN & P1SwMask; /* read switches from p1 */
  P1IES= p1Val;                 /* interrupt on value change */
  P1IFG = 0;                    /* clear pending P1 interrupts  */
  if (!(p1Val & SW1) && (oldP1SwVal & SW1)) /* transition from unpressed to pressed? */
    resetBird();                           /* re-initialize paddle */
  oldP1SwVal = p1Val;
}

/* Switches on P2 (direction pad) */
interrupt(PORT2_VECTOR) Port_2(void)
{
  unsigned char p2Val = P2IN & P2SwMask; /* read switches from p2 */
  P2IES= p2Val;                 /* interrupt on value change */
  P2IFG = 0;                    /* clear pending P2 interrupts  */
  /* just remember button state */
  oldP2SwVal = p2Val;
}

updateBird()
{
  int hover=1;
  /* reverse ball direction at court boundaries
     if ( (birdXPos == 0) || (birdXPos == MAX_X -2))
     birdXVel = -birdXVel;*/
  //bird is always falling
  if ( birdYPos<=MAX_Y )
    birdYPos -= birdYVel;
  drawBird(birdXPos,birdYPos);
  //when clicked, the bird 'flaps' and moves up slightly
  if (!(oldP2SwVal & UpSw)) {
    birdYPos += (birdYVel-5);
    drawBird(birdXPos,birdYPos);
    while ( hover<4 ) {
      birdYPos -= birdYVel; // -= hover;
      //TODO does the bird move in the x-direction also?
      drawBird(birdXPos+2, birdYPos);
      birdYPos += birdYVel/2;
      drawBird(birdXPos,birdYPos);
      hover++;
    }
  } else {
    birdYPos += birdYVel;//=1;
    // draw bird
    //birdXPos += birdXVel;
    drawBird(birdXPos, birdYPos);
  }
}

/* timer interrupt */
interrupt(TIMER0_A0_VECTOR) Timer_0(void)
{
  static int clockDivide = 0;
  if (clockDivide++ > 20) { //7
    updateBird();
    clockDivide = 0;
  }
}

void resetBird(void)
{
  //birdXPos = 43, birdYPos = 34, = center
  birdXPos = 10;
  birdYPos = 34;

  birdXVel = 1; //right
  birdYVel = 1; //
  drawBird(birdXPos, birdYPos);
  //drawPipe(pipe);
  //ddrawPipe
}
