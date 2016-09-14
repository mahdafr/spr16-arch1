#include "draw_pipe.h"
#define pipeRadius 4		/* pipe radius */

void drawAllStatic(void); //draws pipes on board (not moving)
void newOpening(void); //"randomizes" pipe gaps

static u_char pipePos, gapTop, oldGapTop = 0;
static u_char pipe = 0, counter = 0;

u_char pipeChunk(u_char col, u_char rowMajor) {
  u_char chunk = 0;		/* default: transparent */
  signed char deltaX, deltaY;
  u_char dotYMajor, dotYMinor;
  // horiz dist from cursor center (+ for right)
  deltaX = (signed)pipePos - (signed)col;
  // col more than CRADIUS from cursor center?
  if (max(deltaX, -deltaX) > pipeRadius)
    return 0;   /* no dot */

  if (deltaX == 0)
    deltaY = 0;
  else if (deltaX > 0)		/* right of cursor */
    deltaY = deltaX - pipeRadius;
  else 	 // deltaX < 0
    deltaY = deltaX + pipeRadius;

  //if this deltaX is within the boundaries of [-pipeRadius,pipeRadius]
  if ( -deltaX>=-pipeRadius && deltaX<=pipeRadius+2 ) {
    for ( deltaY=gapTop-5 ; deltaY<=gapTop+25 ; deltaY++ ) {
      //the gap
      if ( deltaY>=gapTop && deltaY<=gapTop+20 ) continue;
      //the pipe
      dotYMinor = lcd_getYMinor(deltaY);
      dotYMajor = lcd_getYMajor(deltaY);
      if ( dotYMajor==rowMajor ) /* dotY in this chunk? */
	chunk += chunkMasks[dotYMinor] ^ chunkMasks[dotYMinor+1];
    }
  }
  if ( -deltaX>=-pipeRadius+2 && deltaX<=pipeRadius ) {
    for ( deltaY=0 ; deltaY<=MAX_Y ; deltaY++ ) {
      //the gap
      if ( deltaY>=gapTop-5 && deltaY<=gapTop+25 ) continue;
      //the pipe
      dotYMinor = lcd_getYMinor(deltaY);
      dotYMajor = lcd_getYMajor(deltaY);
      if ( dotYMajor==rowMajor ) /* dotY in this chunk? */
	chunk += chunkMasks[dotYMinor] ^ chunkMasks[dotYMinor+1];
    }
  }
  oldGapTop = gapTop;
  return chunk;
}

u_char firstPipeGapTop = 35, secondPipeGapTop = 20, thirdPipeGapTop = 45;

u_char updatePipe(u_char start, u_char score) {
  //drawAllStatic();
  u_char col, rowMajor, chunk, drawingFirst;
  static u_char prevPipePos = MAX_X/2;
  pipePos = 0;
  u_char firstPipeGap;
  //clean up up to first pipe
  for ( col=0 ; col<start ; col++ )
    for ( rowMajor=0 ; rowMajor<9 ; rowMajor++ )
      lcd_writeChunkAddr(0,col,rowMajor);
  //draw the pipes from the new position
  for ( col=start ; col<MAX_X ; col++ ) {
    counter++;
    if ( col%pipeRadius==2 ) {
      pipePos = col + pipeRadius;
      
      //remember current position
      prevPipePos = pipePos;
      oldGapTop = gapTop;

      if ( start<=32 ) {
	if ( col<=32 )
	  gapTop = thirdPipeGapTop;
	if ( col>32 && col<64 )
	  gapTop = firstPipeGapTop;
	if ( col>=64 )
	  gapTop = secondPipeGapTop;
      }
      if ( start>=32 && start<=64 ) {
	if ( col<=32 )
	  gapTop = secondPipeGapTop; //firstPipeGapTop;
	if ( col>=32 && col<=64 )
	  gapTop = thirdPipeGapTop; //secondPipeGapTop;
	if ( col>=64 )
	  gapTop = firstPipeGapTop; //thirdPipeGapTop;
      }
      if ( start>=64 ) {
	if ( col<=32 )
	  gapTop = firstPipeGapTop;
	if ( col>=32 && col<=64 )
	  gapTop = secondPipeGapTop;
	if ( col>=64 )
	  gapTop = thirdPipeGapTop;
      }

      //determine extent of rectangle around both old & new cursor
      u_char leftCol = min(pipePos, prevPipePos) - pipeRadius;
      u_char rightCol = max(pipePos, prevPipePos) + pipeRadius;    
      for ( col=leftCol ; col<=rightCol ; col++ )
	for ( rowMajor=0 ; rowMajor<9 ; rowMajor++ ) {
	  if ( rightCol>=MAX_X ) {
	    //if the pipe reaches past the right boundary of the LCD
	    chunk = pipeChunk(MAX_X-pipeRadius,rowMajor);
	    lcd_writeChunkAddr(chunk,MAX_X-pipeRadius,rowMajor);
	  } else {
	    //if the pipe is in within the boundary of the LCD
	    chunk = pipeChunk(col,rowMajor);
	    lcd_writeChunkAddr(chunk,col,rowMajor);
	  }
	  char scr[] = "     ";
	  itoa(score,scr,10);
	  chunk -= lcd_writeString(scr,75,1); //write
	  lcd_writeChunkAddr(chunk,col,rowMajor);
	}
      chunk = 0;
      for (   ; col<=prevPipePos+7*pipeRadius ; col++ )
	for ( rowMajor=0 ; rowMajor<9 ; rowMajor++ ) {
	  char scr[] = "     ";
	  itoa(score,scr,10);
	  chunk -= lcd_writeString(scr,75,1); //write
	  lcd_writeChunkAddr(chunk,col,rowMajor);
	}
      col = prevPipePos + 7*pipeRadius;
    }
  }
  return firstPipeGap;
}
void newOpening() {
  switch ( counter%4 ) {
    case 0:
      gapTop -= 15;
      break;
    case 1:
      gapTop += 25;
      break;
    case 2:
      gapTop -= 30;
      break;
    case 3:
      gapTop += 20;
      break;
  }
  //gap is too close to the bottom or top
  if ( gapTop>=MAX_Y-15 || gapTop<=-20 )
    gapTop = 35;
  if ( gapTop>=MAX_Y-20 || gapTop<=20 )
    gapTop = 35;
  else
    gapTop -= 15;
  oldGapTop = gapTop;
}

void drawAllStatic() {
  u_char col, rowMajor, chunk; static u_char prevPipePos;
  pipePos = 0;
  for ( col= 25 ; col<MAX_X ; col++ ) {
    if ( col%pipeRadius==2 ) {
      pipePos = col + pipeRadius;
      
      //generate new gap for the new pipe
      //oldGapTop = gapTop;
      //if ( oldGapTop>gapTop ) gapTop -= 25; //was lower so move up
      //else gapTop += 25; //was higher so move lower
      if ( gapTop>=MAX_Y-20 || gapTop<=20 )
	gapTop = 35;
      else
	gapTop -= 15;
      //remember current position
      prevPipePos = pipePos;
      oldGapTop = gapTop;

      //determine extent of rectangle around both old & new cursor
      u_char leftCol = min(pipePos, prevPipePos) - pipeRadius;
      u_char rightCol = max(pipePos, prevPipePos) + pipeRadius;    
      for ( col=leftCol ; col<=rightCol ; col++ )
	for ( rowMajor=0 ; rowMajor<9 ; rowMajor++ ) {
	  if ( rightCol>=MAX_X ) {
	    chunk = pipeChunk(MAX_X-pipeRadius,rowMajor);
	    lcd_writeChunkAddr(chunk,MAX_X-pipeRadius,rowMajor);
	  } else {
	    chunk = pipeChunk(col,rowMajor);
	    lcd_writeChunkAddr(chunk,col,rowMajor);
	  }
	}
      col = prevPipePos  + 6*pipeRadius;
    } else {
      //do not draw anything in this column
      //for ( rowMajor=0 ; rowMajor<9 ; rowMajor++ )
	//lcd_writeChunkAddr(0,col,rowMajor);
    }
  }
}
