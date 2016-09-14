#include <msp430g2553.h>
#include "lcd_utils.h"
#include "drawPaddle.h"

#define PADDLE_START_POSITION 30


#include "paddleButtons.h"
#define P1SwMask SW1
#define P2SwMask (UpSw + DownSw + LeftSw + RightSw)
unsigned char oldP1SwVal, oldP2SwVal;


/* setup switch interrupts */
void initializeSwitchInterrupts() 
{
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
u_char paddleY = PADDLE_START_POSITION;

void resetPaddle(void);	/* forward definition */

void main(void) 
{  
  WDTCTL = WDTPW + WDTHOLD;     // Stop watchdog timer
  lcdinit();                    // init LCD (also: CPU clock to 16MHz)
  lcd_setAddr(0,3);
  CCTL0 = CCIE;                 // CCR0 interrupt enabled
  TACTL = TASSEL_2 + MC_1 + ID_3; // Set timer clock to CPU clock/8
  CCR0 = 50000;			// Interrupt every 10 ms
  initializeSwitchInterrupts();
  resetPaddle();
  or_sr(0x18);			// CPU off, GIE on
}  

/* Switches on P1 (far right switch - used to reset the game) */
interrupt(PORT1_VECTOR) Port_1(void)
{
  unsigned char p1Val = P1IN & P1SwMask; /* read switches from p1 */
  P1IES= p1Val;			/* interrupt on value change */
  P1IFG = 0;			/* clear pending P1 interrupts  */
  if (!(p1Val & SW1) && (oldP1SwVal & SW1)) /* transition from unpressed to pressed? */
    resetPaddle();			   /* re-initialize paddle */
  oldP1SwVal = p1Val;
}

/* Switches on P2 (direction pad - used to move paddle up & down) */
interrupt(PORT2_VECTOR) Port_2(void)
{
  unsigned char p2Val = P2IN & P2SwMask; /* read switches from p2 */
  P2IES= p2Val;			/* interrupt on value change */
  P2IFG = 0;			/* clear pending P2 interrupts  */
  /* just remember button state */
  oldP2SwVal = p2Val;
}


void updatePaddle(void)		/* called by timer interrupt handler */
{
  // check if up switch is pressed
  if (!(oldP2SwVal & UpSw))  {
    if (paddleY > 6)
        paddleY--;
    drawPaddle(paddleY);
  }
  // check if down switch is pressed
  if (!(oldP2SwVal & DownSw)) {
    paddleY++;
    drawPaddle(paddleY);
  }
}

/* timer interrupt */
interrupt(TIMER0_A0_VECTOR) Timer_0(void)
{
  updatePaddle();
}

  
void resetPaddle(void)
{
  paddleY = PADDLE_START_POSITION;  
  drawPaddle(paddleY);
}
