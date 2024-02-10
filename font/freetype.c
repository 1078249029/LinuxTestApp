#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <linux/fb.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <wchar.h>
#include <sys/ioctl.h>
#include <ft2build.h>
#include "font_manager.h"
#include FT_FREETYPE_H
#include FT_GLYPH_H

#define DefaultFontSize 12

FT_Library	  library;
FT_Face 	  face;
FT_Vector     pen;
FT_GlyphSlot  slot;


int FreetypeInit(char *FontFileName)
{
	int error;

	/* 显示矢量字体 */
	error = FT_Init_FreeType( &library );			   /* initialize library */
	/* error handling omitted */
	
	error = FT_New_Face( library, FontFileName, 0, &face ); /* create face object */
	/* error handling omitted */	
	if (error)
	{
		printf("FreetypeInit error\n");
		return -1;
	}
	FT_Set_Pixel_Sizes(face, DefaultFontSize, 0);
	return 0;
}

int FreetypeSetSize(int size)
{
	FT_Set_Pixel_Sizes(face, size, 0);
	return 0;
}

int FreetypeGetBuf(unsigned int dwCode, pFontBitMap BitMap)
{
	int error;
	pen.x = BitMap->iOriginX * 64; /* 单位: 1/64像素 */
    pen.y = BitMap->iOriginY * 64; /* 单位: 1/64像素 */

	FT_Set_Transform(face, 0, &pen);

	
    error = FT_Load_Char( face, dwCode, FT_LOAD_RENDER );
	if (error)
	{
		printf("FT_Load_Char error\n");
		return -1;
	}
	

	slot = face->glyph;
	BitMap->Region.iWidth = slot->bitmap.width;
	BitMap->Region.iHeigh = slot->bitmap.rows;
	BitMap->pucBuf = slot->bitmap.buffer;
	BitMap->Region.iLeftUpX = slot->bitmap_left;
	BitMap->Region.iLeftUpY = BitMap->iOriginY*2 - slot->bitmap_top;
	BitMap->iOriginNextX = BitMap->iOriginX + slot->advance.x / 64;;
    BitMap->iOriginNextY = BitMap->iOriginY;
	return 0;
}

struct FontOpr FreetypeOpr = {
	.name = "freetype",
	.Init = FreetypeInit,
	.SetSize = FreetypeSetSize,
	.GetBuf = FreetypeGetBuf,
};

void FreetypeRegister(void)
{
	InsertFontList(&FreetypeOpr);
}



