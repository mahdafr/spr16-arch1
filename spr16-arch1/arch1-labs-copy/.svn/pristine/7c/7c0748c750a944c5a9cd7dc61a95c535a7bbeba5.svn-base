#ifndef _DRAW_TILE_H
#define _DRAW_TILE_H
#include "lcd_utils.h"

/* couple of useful expressions */
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

/* starting positions */
#define SHAPE_START_Y_POSITION 32
#define SHAPE_START_X_POSITION 32

/* arena boundaries */
#define GAP            18	
#define ARENA_LEFT     GAP
#define ARENA_RIGHT    (MAX_X-GAP)
#define ARENA_TOP      GAP
#define ARENA_BOT      (MAX_Y-GAP)


/* square components */
#define TOP_CRN          (chunkMasks[8] ^ chunkMasks[4]) // 0xf0
#define TOP_LIN          (chunkMasks[5] ^ chunkMasks[4]) // 0x10          
#define BTM_CRN          (chunkMasks[4] ^ chunkMasks[0]) // 0x0f
#define BTM_LIN          (chunkMasks[5] ^ chunkMasks[4]) // 0x08

void drawArena(void);		/* draw entire arena (should be called once) */
u_char arenaChunk(u_char x, u_char rowMajor);
void updateCursor(u_char x, u_char y); /* draw/update cursor */
u_char cursorChunk(u_char x, u_char rowMajor);


#endif //_DRAW_TILE_H
