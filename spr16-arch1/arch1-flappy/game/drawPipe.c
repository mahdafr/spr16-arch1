#include "lcd_utils.h"
#include "drawPipe.h"

#define pipeRadius 4
#define pipeHeight 68

#define getYMajor lcd_getYMajor 
#define getYMinor lcd_getYMinor
#define write lcd_writeChunk

static u_char oldPipeTopMajor, oldPipeBotMajor, oldPipeTopMajor2, oldPipeBotMajor2;
static u_char oldPipeLeft, oldPipeRight;
static u_char pipeLeft, pipeRight, boundLeft, boundRight;

void drawPipe(u_char pipeX, u_char gapHeight, u_char gapTop) {
  // pipe left & right rectangular window that includes old & new pipe
  //the upper part of the pipe
  u_char pipeTop = pipeHeight - pipeHeight; //top of the LCD: 0
  u_char pipeBot = gapTop; //bottom of the top part of the pipe
  u_char pipeTopMajor = getYMajor(pipeTop);
  u_char pipeBotMajor = getYMajor(pipeBot);

  //the lower part of the pipe
  u_char pipeTop2 = gapTop + gapHeight; //do not draw in the gap
  u_char pipeBot2 = pipeHeight; //bottom of the LCD: 68
  u_char pipeTopMajor2 = getYMajor(pipeTop2);
  u_char pipeBotMajor2 = getYMajor(pipeBot2);

  //the left and right bounds of the pipe: old to new
  pipeLeft = pipeX - pipeRadius;
  pipeRight = pipeX + pipeRadius;
  // bounding rectangle surrounding old & new pipe
  boundLeft = min(oldPipeLeft, pipeLeft);    // left col
  boundRight = max(oldPipeRight, pipeRight); // right col

  //for the upper part
  u_char rowMajor = min(oldPipeTopMajor, pipeTopMajor);      // top chunk number
  u_char rowMajorBound = max(oldPipeBotMajor, pipeBotMajor); // bot chunk number
  u_char chunkTop = lcd_majorToY(rowMajor); // top row of top chunk
  //for the lower part
  u_char rowMajor2 = min(oldPipeTopMajor2, pipeTopMajor2);      // top chunk number
  u_char rowMajorBound2 = max(oldPipeBotMajor2, pipeBotMajor2); // bot chunk number
  u_char chunkTop2 = lcd_majorToY(rowMajor2); //top row of top chunk for bottom pipe

  for ( ; rowMajor<=rowMajorBound, rowMajor2<=rowMajorBound2 ;	    // for all affected chunk #s
	rowMajor++, chunkTop+=8, rowMajor2++, chunkTop2+=8 ) {	    // next chunk
    lcd_setAddr(boundLeft, rowMajor);
    u_char chunk = 0, col;
    //upper part of the pipe
    if ( rowMajor>=pipeTopMajor && rowMajor<=pipeBotMajor ) { 
      u_char chunkBot = chunkTop + 7;
      u_char bitsMin = getYMinor(max(chunkTop, pipeTop)); // bits to set
      u_char bitsMax = getYMinor(min(chunkBot, pipeBot));
      u_char numBitsToSet = 1 + (bitsMax - bitsMin);
      chunk = set_range(numBitsToSet, bitsMin);
    }
    //lower part of the pipe
    if ( rowMajor2>=pipeTopMajor2 && rowMajor2<=pipeBotMajor2 ) { 
      u_char chunkBot2 = chunkTop2 + 7;
      u_char bitsMin2 = getYMinor(max(chunkTop2, pipeTop2)); // bits to set
      u_char bitsMax2 = getYMinor(min(chunkBot2, pipeBot2));
      u_char numBitsToSet2 = 1 + (bitsMax2 - bitsMin2);
      chunk += set_range(numBitsToSet2, bitsMin2);
    }
    for ( col=boundLeft ; col<pipeLeft ; col++ ) //left of pipe
      write(0);
    for ( ; col<=pipeRight ; col++ ) //pipe
      write(chunk);
    for ( ; col<=boundRight ; col++) //right of pipe
      write(0);
  }

  oldPipeTopMajor = pipeTopMajor;
  oldPipeBotMajor = pipeBotMajor;
  oldPipeLeft = pipeLeft;
  oldPipeRight = pipeRight;
}
