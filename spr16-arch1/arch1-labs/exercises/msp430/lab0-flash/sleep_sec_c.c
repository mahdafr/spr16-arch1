/** 
 * sleep_c.c - Example sleep function in c.
 * 
 * @author Adrian Veliz
 * @author Eric Freudenthal
 * @version 0.1.20130815
 */

#include "blink.h"

void sleep(unsigned short seconds) {
  while (seconds--) {
    int sixHundreths = 600;
    while (sixHundreths--)
      sleep_600th();
  }
}
