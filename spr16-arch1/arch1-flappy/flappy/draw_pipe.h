#ifndef _DRAW_TILE_H
#define _DRAW_TILE_H
#include "lcd_utils.h"
#include "score_demo.h"

/* couple of useful expressions */
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

/* square components */
#define TOP_CRN          (chunkMasks[8] ^ chunkMasks[4]) // 0xf0
#define TOP_LIN          (chunkMasks[5] ^ chunkMasks[4]) // 0x10          
#define BTM_CRN          (chunkMasks[4] ^ chunkMasks[0]) // 0x0f
#define BTM_LIN          (chunkMasks[5] ^ chunkMasks[4]) // 0x08

static u_char pipeStartPos[5], pipeGap[5];

void updatePipe(u_char x); /* draw/update pipe */
u_char pipeChunk(u_char x, u_char rowMajor);
void updateCursor(u_char x, u_char y);
u_char cursorChunk(u_char x, u_char rowMajor);

#endif //_DRAW_TILE_H
