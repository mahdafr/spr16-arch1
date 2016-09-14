#include "lcd_utils.h"
#include "drawBall.h"
static u_char oldBallTopMajor, oldBallBotMajor, oldBallLeft, oldBallRight;
#define ballRadius 2
#define getYMajor lcd_getYMajor 
#define getYMinor lcd_getYMinor

void drawBall(u_char ballX, u_char ballY) {
  /* compute:     ball left & right
     rectangular window that includes old & new ball */
  u_char ballTop = ballY - ballRadius, ballBot = ballY + ballRadius;
  u_char ballTopMajor = getYMajor(ballTop), ballBotMajor = getYMajor(ballBot);
  u_char ballLeft = ballX - ballRadius, ballRight = ballX + ballRadius;
  /* bounding rectangle surrounding old & new ball */
  u_char boundLeft = min(oldBallLeft, ballLeft);    /* left col */
  u_char boundRight = max(oldBallRight, ballRight); /* right col */

  u_char rowMajor = min(oldBallTopMajor, ballTopMajor);      /* top chunk number */
  u_char rowMajorBound = max(oldBallBotMajor, ballBotMajor); /* bot chunk number */
  u_char chunkTop = lcd_majorToY(rowMajor); /* top row of top chunk */
  for (; rowMajor <= rowMajorBound;	    /* for all affected chunk #s */
       rowMajor++, chunkTop += 8) {	    /* next chunk */
    lcd_setAddr(boundLeft, rowMajor);
    u_char chunk = 0, col;
    if (rowMajor >= ballTopMajor && rowMajor <= ballBotMajor) { 
      u_char chunkBot = chunkTop + 7;
      u_char bitsMin = getYMinor(max(chunkTop, ballTop)); /* bits to set */
      u_char bitsMax = getYMinor(min(chunkBot,ballBot));
      u_char numBitsToSet = 1 + (bitsMax - bitsMin);
      chunk = set_range(numBitsToSet/*&&0x0001111*/, bitsMin);
    }
    for (col = boundLeft; col < ballLeft; col++) /* left of ball */
      lcd_writeChunk(0);			 
    for (; col <= ballRight; col++) /* ball */
      lcd_writeChunk(chunk);
    for (; col <= boundRight; col++) /* right of ball */
      lcd_writeChunk(0);
  }
  oldBallTopMajor = ballTopMajor; oldBallBotMajor = ballBotMajor;
  oldBallLeft = ballLeft; oldBallRight = ballRight;
}
