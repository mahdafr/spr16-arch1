#include "lcd_utils.h"
#include "drawPaddle.h"

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

#define paddleSize 3		/* # of pixels above and below paddle position middle */

// old paddle top and bottoms
static u_char oldPaddleTopYMajor, oldPaddleBotYMajor;

void drawPaddle(u_char yPos)	/* ypos is middle of paddle */
{
  u_char paddleTop = yPos - paddleSize, paddleBot = yPos + paddleSize;
  u_char paddleTopYMajor = lcd_getYMajor(paddleTop);
  u_char paddleBotYMajor = lcd_getYMajor(paddleBot);

  /* upper and lower bounds of affected pixels */
  u_char yMajor = min(paddleTopYMajor, oldPaddleTopYMajor); /* top of affected region */
  u_char chunkTop = lcd_majorToY(yMajor); /* top row of affected region  */
  u_char yMajorBound = max(paddleBotYMajor, oldPaddleBotYMajor); /* max yMajor affected */

  /* write each affected yMajor exactly once */
  for (; yMajor <= yMajorBound;	/* max yMajor affected */
       yMajor++, chunkTop += 8) { /* next chunk */
    lcd_setAddr(0, yMajor);	/* paddle in col zero */
    u_char chunk = 0;
    u_char chunkBot = chunkTop + 7; /* bottom row of current chunk */
    if (yMajor >= paddleTopYMajor && yMajor <= paddleBotYMajor) { 
      u_char bitsMin = lcd_getYMinor(max(chunkTop, paddleTop)); /* bits to set */
      u_char bitsMax = lcd_getYMinor(min(chunkBot,paddleBot));
      u_char numBitsToSet = 1 + (bitsMax - bitsMin);
      chunk = set_range(numBitsToSet, bitsMin);
    }
    lcd_writeChunk(chunk); lcd_writeChunk(chunk); /* paddle 2 pixels wide */
  }
  oldPaddleBotYMajor = paddleBotYMajor; /* remember state */
  oldPaddleTopYMajor = paddleTopYMajor;
}

