#include "msp430g2553.h"
#include "config_clocks.h"
#include "blink.h"

void dimmer() {
  unsigned short i = 0, j = 0;
  for (  ;  ;  ) {
    //brightest at 90% on/10% off
    i = 5000;
    while ( (i--)!=0 ) {
      if ( i%10 ) led_control(1);
      else led_control(0);
      //for ( j=0 ; j<5 ; j++ )
      //sleep_600th();
    }

    //dim to med: 40% on/60% off
    i = 5000;
    while ( (i--)!=0 ) {
      if ( i%10<4 ) led_control(1);
      else led_control(0);
      //for ( j=0 ; j<5 ; j++ )
      //sleep_600th();
    }

    //dimmest at 10% on/90% off
    i = 5000;
    while ( (i--)!=0 ) {
      if ( i%10 ) led_control(0);
      else led_control(1);
      //for ( j=0 ; j<5 ; j++ )
      //sleep_600th();
    }
  }
}

int main(void) {
  //turns timer off
  WDTCTL = WDTPW + WDTHOLD;
  configureClocks();

  *(char *)0x0022 = 0x0041;
  dimmer();
  return 0;
}
