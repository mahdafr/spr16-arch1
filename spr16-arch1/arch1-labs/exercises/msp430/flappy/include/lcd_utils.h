#ifndef lcd_utils_included

#include "booster1202.h"
#include "lcd_backend.h"

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

/* compute major & minor row numbers */
// 8 pixels (1 byte) per chunk, bit zero at top
#define lcd_getYMajor(_y) ((_y) >> 3)  // y / 8
#define lcd_getYMinor(_y) ((_y) & 7)   // y % 8

/* compute top row of major */
#define lcd_majorToY(_major) ((_major) << 3)

/* displays a chunk (byte of binary pixels) at the given address */
void lcd_setAddr(u_char x, u_char yMajor); /* set addr of next write  */
void lcd_writeChunk(char chunk); /* write chunk and increment x */

/* set addr & write */
void lcd_writeChunkAddr(char chunk, u_char xPos, u_char yMajor); 

/* converts ints to character sequences */
char* itoa(int value, char* result, int base);

// masks used to clear bits from chunks
// least significant i bits are 1 in chunkMasks[i] 
extern const u_char chunkMasks[9];

#ifdef USE_SHIFT      /* MSP430 has no op for multi-bit shift */
# define set_bits(_numBits) ((1<<(_numBits))-1)
# define set_range(_nSet, _shift) (set_bits(_nSet) << _shift)
#else                 /* on MSP430 arrays are faster than multi-shift */
# define set_bits(_numBits) chunkMasks[_numBits]
# define set_range(_b, _shft) (set_bits((_b)+(_shft)) ^ set_bits(_shft))
#endif  // USE_SHIFT

#define invert_range(_nb, _shft, _val) ((_val) ^ set_range(_nb, _shft))

#define lcd_utils_included
#endif // lcd_utils_included
