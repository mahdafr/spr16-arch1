#include "lcd_utils.h"

void lcd_writeChunk(char chunk)
{
  writeToLCD(LCD1202_DATA, chunk);
}

void lcd_writeChunkAddr(char chunk, u_char xAddr, u_char yAddr)
{
  // set address on LCD
  lcd_setAddr(xAddr, yAddr);
  
  // write display data to the LCD
  lcd_writeChunk(chunk);
}

// masks used to clear bits from chunks
// least significant i bits are 1 in chunkMasks[i] 
const u_char chunkMasks[9] = {0x0, 0x1, 0x3, 0x7, 0xf, 0x1f, 0x3f, 0x7f, 0xff};

