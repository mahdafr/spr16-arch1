#include <msp430g2553.h>
#include "lcd_utils.h"
#include "lcd_char.h"
#include "drawPaddle.h"
#include "paddleButtons.h"


/* global vars */
short score;

void resetScore(void);
void updateScore(void);


unsigned char oldP1SwVal, oldP2SwVal;

#define P1SwMask SW1
#define P2SwMask (UpSw + DownSw + LeftSw + RightSw)

void initializeSwitchInterrupts()	/* setup interrupts on switch */
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


void main(void) 
{  
  WDTCTL = WDTPW + WDTHOLD;     // Stop watchdog timer
  lcdinit();                    // init LCD (also: CPU clock to 16MHz)
  CCTL0 = CCIE;                 // CCR0 interrupt enabled
  TACTL = TASSEL_2 + MC_1 + ID_3; // Set timer clock to CPU clock/8
  CCR0 = 50000;			// Interrupt every 10 ms
  initializeSwitchInterrupts();
  resetScore();
  or_sr(0x18);			// CPU off, GIE on
}  

/* Switches on P1 (far right switch) */
interrupt(PORT1_VECTOR) Port_1(void)
{
  unsigned char p1Val = P1IN & P1SwMask; /* read switches from p1 */
  P1IES= p1Val;			/* interrupt on value change */
  P1IFG = 0;			/* clear pending P1 interrupts  */
  if (!(p1Val & SW1) && (oldP1SwVal & SW1)) /* transition from unpressed to pressed? */
    resetScore();			   /* re-initialize score */
  oldP1SwVal = p1Val;
}

/* Switches on P2 (direction pad) */
interrupt(PORT2_VECTOR) Port_2(void)
{
  unsigned char p2Val = P2IN & P2SwMask; /* read switches from p2 */
  P2IES= p2Val;			/* interrupt on value change */
  P2IFG = 0;			/* clear pending P2 interrupts  */
  /* no use for direction buttons in this program */
  oldP2SwVal = p2Val;
}

void updateScore(void)		/* called indirectly from timer interrupt handler */
{
  char numString[] = "     ";
  
  // increase score for each pass
  score++;
  
  // blank score area
  lcd_writeString("     ",72,0);
  
  // convert integer to chars
  itoa(score, numString, 10);
  
  // write score to screen
  lcd_writeString(numString,72,0);
}

void resetScore(void)
{  
  score = 0;
}

/* timer interrupt */
interrupt(TIMER0_A0_VECTOR) Timer_0(void)
{
  static int clockDivide = 0;
  if (clockDivide++ > 20) {
    updateScore();
    clockDivide = 0;
  }
}

