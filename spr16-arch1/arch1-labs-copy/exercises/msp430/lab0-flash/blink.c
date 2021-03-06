/** 
 * Alternate Red and Greed LEDs every second.
 * 
 * @author Adrian Veliz
 * @author Eric Freudenthal
 * @version 0.1.20130815
 */

#include "msp430g2553.h"
#include "config_clocks.h"
#include "blink.h"

int main(void) {
  WDTCTL = WDTPW + WDTHOLD;     /* Don't touch. Will be explained later. */
  configureClocks();		/* Don't touch. Will be explained later. */

  *(char *)0x0022 = 0x0041; 	/* P1DIR: set bits 0 and 6 of P1 to output  */

  for (;;) {
    led_control(0);
    sleep(1);
    led_control(1);
    sleep(1);
  }
  return 0;
}


