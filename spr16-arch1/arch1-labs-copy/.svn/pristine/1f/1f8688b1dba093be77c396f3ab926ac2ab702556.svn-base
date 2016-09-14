/** 
 * Alternate Red and Greed LEDs every second.
 * 
 * @author Adrian Veliz
 * @author Eric Freudenthal
 * @version 0.1.20130815
 */

#include "msp430g2553.h"
#include "blink.h"

#define P1OUT_ADDR 0x21

void led_control(unsigned short v) {
  //if (v) *((char *)P1OUT_ADDR) = 0x0040;           /* green; bit 6 of P1 */
  if ( v )*((char *)P1OUT_ADDR) = 0x0001;             /* red; bit 0 of P1 */
  else *((char *)P1OUT_ADDR) = 0x0000;
}

/*
//for lab on 03.23 W 1:30p
void activate() {
  unsigned short s=0;
  for ( ; ; s=1-s  ) {
    //alternate
    led_control(s);
    sleep(s);
  }
}
//to make it off->red->green->both->off->...
//if ( v ) *((char *)P1OUT_ADDR) = 0x40, 0b01000000;
*/
