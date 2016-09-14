/*Modified by: Christopher McKye
  Lab 2 - Team two: X cursor modification
  5/1/16
*/

#include "draw_pipe.h"
#include "lcd_utils.h"
#define CRADIUS 5	/* cursor radius */
//static u_char oldCursorX, oldCursorY;
static u_char cursorX, cursorY;
static u_char oldTopMajor, oldBotMajor, oldLeft, oldRight;  
u_char cursorChunk(u_char col, u_char rowMajor)
{
  
  u_char chunk = 0;		/* default: transparent */

  signed char deltaY;
  u_char dotYMajor, dotYMinor, dotY, dotX;

  // horiz dist from cursor center (+ for right)
  signed char deltaX = (signed)cursorX - (signed)col;
  // col more than CRADIUS from cursor center?
  if (max(deltaX, -deltaX) > CRADIUS){		      
     return 0;
  }
  if (deltaX == 0){
    deltaY = 0; //center dot
  }else if (deltaX > 0){		/* right of cursor */
    deltaY = deltaX - CRADIUS;
  }else{
    deltaY = deltaX + CRADIUS; // moves the right slash up or down
  }
  //int i;
  //Draw left and right columns 
  if ((deltaX == -CRADIUS) || deltaX == CRADIUS){
   for(deltaY = -2; deltaY <= 2; deltaY++){
     dotY = cursorY - deltaY;
     dotYMinor = lcd_getYMinor(dotY);
     dotYMajor = lcd_getYMajor(dotY);

      if (dotYMajor == rowMajor){
	chunk+=chunkMasks[dotYMinor]^chunkMasks[dotYMinor+1];
      }
     }
  }
  
  //Draw row major 0 left and right steps desending
  int i;
  for (i = 1;i <= CRADIUS;i++){  
    if ((deltaX == (-CRADIUS+i)) || (deltaX == (CRADIUS-i))){
      
      //Desend by 1
      if((deltaX == -CRADIUS) || (deltaX == CRADIUS)){
	//Decrease Y by 1 for step
      	if (deltaX == -2){
      	  deltaY-=2;
      	  dotY = cursorY - deltaY;
      	}else{
	  deltaY+=2;
      	  dotY = cursorY - deltaY;
      	}
	//	Set Minor and Major
      	dotYMinor = lcd_getYMinor(dotY);
      	dotYMajor = lcd_getYMajor(dotY);
	//Set chunks for writing
      	if (dotYMajor == rowMajor){
      	  chunk+=chunkMasks[dotYMinor]^chunkMasks[dotYMinor+1];
	}
       }
   
      //Descend by 2
      /* if((deltaX == -3) || (deltaX == 3)){
	//Decrease Y by 1 for step
	if (deltaX == -3){
	  deltaY+=1;
	  dotY = cursorY - deltaY;
	}else{
	  deltaY+=5;
	  dotY = cursorY - deltaY;
	}
	//Set Minor and Major
	dotYMinor = lcd_getYMinor(dotY);
	dotYMajor = lcd_getYMajor(dotY);
	//Set chunks for writing
	if (dotYMajor == rowMajor){
	  chunk+=chunkMasks[dotYMinor]^chunkMasks[dotYMinor+1];
	}
      }*/
      //Descend by 3
        if ((deltaX == -4) || (deltaX == 4)){
	//Decrease Y by 1 for step
	if (deltaX == -4){
	  deltaY+=3;
	  dotY = cursorY - deltaY;
	}else{
	  deltaY+=5;
	  dotY = cursorY - deltaY;
	}
	//Set Minor and Major
	dotYMinor = lcd_getYMinor(dotY);
	dotYMajor = lcd_getYMajor(dotY);
	//Set chunks for writing
	if (dotYMajor == rowMajor){
	  chunk+=chunkMasks[dotYMinor]^chunkMasks[dotYMinor+1];
	}
      }

	/* if ((deltaX == -4) || (deltaX == 4)){
	//Decrease Y by 1 for step
	if (deltaX == -4){
	  deltaY-=3;
	  dotY = cursorY - deltaY;
	}else{
	  deltaY-=5;
	  dotY = cursorY - deltaY;
	}
	//Set Minor and Major
	dotYMinor = lcd_getYMinor(dotY);
	dotYMajor = lcd_getYMajor(dotY);
	//Set chunks for writing
	if (dotYMajor == rowMajor){
	  chunk+=chunkMasks[dotYMinor]^chunkMasks[dotYMinor+1];
	}
      }   */
      
      //Draw horizaontal rows
	for (deltaY = 3; deltaY <= 3; deltaY++){
	
	  dotY = cursorY - deltaY;
	  dotYMinor = lcd_getYMinor(dotY);
	  dotYMajor = lcd_getYMajor(dotY);
	  if (dotYMajor == rowMajor){
	    chunk+=chunkMasks[dotYMinor]^chunkMasks[dotYMinor+1];
	  }
	}  
      for (deltaY = 4; deltaY <= 4; deltaY++){
	dotY = cursorY - deltaY;
	dotYMinor = lcd_getYMinor(dotY);
	dotYMajor = lcd_getYMajor(dotY);
	if (dotYMajor == rowMajor){
	  chunk+=chunkMasks[dotYMinor]^chunkMasks[dotYMinor+1];
	}
	}
      }
  }

  //Draw row major 1 left and right steps ascending
  for (i=1; i <= 5;i++){
    if ((deltaX == (-CRADIUS+i)) || (deltaX == (CRADIUS-i))){
      
      if((deltaX == -2) || (deltaX == 2)){
	if (deltaX == -2){
	  deltaY-=4;
	  dotY = cursorY + deltaY;
	}else{
	  deltaY-=4;
	  dotY = cursorY + deltaY;
	}
	dotYMinor = lcd_getYMinor(dotY);
	dotYMajor = lcd_getYMajor(dotY);

	if (dotYMajor == rowMajor){
	  chunk+=chunkMasks[dotYMinor]^chunkMasks[dotYMinor+1];
	}
      }  

      
       if((deltaX == -3) || (deltaX == 3)){
	if (deltaX == -3){
	  deltaY-=3;
	  dotY = cursorY + deltaY;
	}else{
	  deltaY-=3;
	  dotY = cursorY + deltaY;
	}
	dotYMinor = lcd_getYMinor(dotY);
	dotYMajor = lcd_getYMajor(dotY);

	if (dotYMajor == rowMajor){
	  chunk+=chunkMasks[dotYMinor]^chunkMasks[dotYMinor+1];
	}
      }   
     
     
      if ((deltaX == -4) || (deltaX == 4)){
	if (deltaX == -4){
	  deltaY-=2;
	  dotY = cursorY + deltaY;
	}else{
	  deltaY-=2;
	  dotY = cursorY + deltaY;
	}
	dotYMinor = lcd_getYMinor(dotY);
	dotYMajor = lcd_getYMajor(dotY);

	if (dotYMajor == rowMajor){
	  chunk+=chunkMasks[dotYMinor]^chunkMasks[dotYMinor+1];
	}
	}  
      
      for (deltaY = 4; deltaY <= 4; deltaY++){
	if (deltaX-=2){
	dotY = cursorY + deltaY;
	}else{
	  dotY = cursorY +deltaY;
	}
	if (deltaX=+2){
	  dotY = cursorY + deltaY;
	}else{
	  dotY = cursorY + deltaY;
	}
	dotYMinor = lcd_getYMinor(dotY);
	dotYMajor = lcd_getYMajor(dotY);
	if (dotYMajor == rowMajor){
	  chunk+=chunkMasks[dotYMinor]^chunkMasks[dotYMinor+1];
	}
      }
      for (deltaY = 5; deltaY <= 5; deltaY++){
	if (deltaX-=2){
	  dotY = cursorY + deltaY;
	}else{
	  dotY = cursorY +deltaY;
	}
	if (deltaX=+2){
	  dotY = cursorY + deltaY;
	}else{
	  dotY = cursorY + deltaY;
	}
	dotYMinor = lcd_getYMinor(dotY);
	dotYMajor = lcd_getYMajor(dotY);
	if (dotYMajor == rowMajor){
	  chunk+=chunkMasks[dotYMinor]^chunkMasks[dotYMinor+1];
	}
      }
    }  
    
    
    }      
  
  //Draw ceneter square
  /*if ((deltaX == -1) || deltaX == 1 || deltaX == 0){
    for(deltaY = -1; deltaY <= 1; deltaY++){
      dotY = cursorY - deltaY;
      dotYMinor = lcd_getYMinor(dotY);
      dotYMajor = lcd_getYMajor(dotY);

      if (dotYMajor == rowMajor){
	chunk+=chunkMasks[dotYMinor]^chunkMasks[dotYMinor+1];
      }
      }
      } */
    
  return chunk;
}  

void updateCursor(u_char x, u_char y)
{
  cursorX = x; cursorY = y;
  static u_char oldCursorX = MAX_X/2, oldCursorY = MAX_Y/2;
  u_char top = y - CRADIUS;
  u_char topMajor = lcd_getYMajor(top);
  u_char bot = y + CRADIUS;
  u_char botMajor = lcd_getYMajor(bot);
  u_char left = x - CRADIUS;
  u_char right = x + CRADIUS;
  
  // determine extent of rectangle around both old & new cursor
  // u_char leftCol = min(cursorX, oldCursorX) - CRADIUS; // /
  // u_char rightCol = max(cursorX, oldCursorX) + CRADIUS;
  u_char leftCol = min(oldLeft, left);
  u_char rightCol = max(oldRight, right);
  //Use min and max of new and old cursor to take care off cursor leaving artifacts
  //when it moves up or down.
  u_char topRowMajor = lcd_getYMajor(min(cursorY, oldCursorY) - CRADIUS);
  u_char botRowMajor = lcd_getYMajor(max(cursorY, oldCursorY) + CRADIUS); // + /

  //u_char rowMajor = min(oldTopMajor, topMajor);      /* top chunk number */
  // u_char rowMajorBound = max(oldBotMajor, botMajor); /* bot chunk number */ 
  // remember current cursor position
  //oldCursorX = cursorX, oldCursorY = cursorY;
  
  // redraw all chunks within old & new cursor
  u_char col, rowMajor;
  int i = 0;

  for (col = leftCol; col <= rightCol; col++){
    u_char chunk = 0;
    for (rowMajor = topRowMajor; rowMajor <= botRowMajor; rowMajor++) {
      chunk = cursorChunk(col, rowMajor);

      lcd_writeChunkAddr(chunk, col, rowMajor);
    }
    }
  oldCursorX = cursorX;
  oldCursorY = cursorY;  
  oldTopMajor = topMajor;
  oldBotMajor = botMajor;
  oldLeft = left;
  oldRight = right;  
}
