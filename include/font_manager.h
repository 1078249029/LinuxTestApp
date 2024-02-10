#ifndef _FONT_MANAGER_H
#define _FONT_MANAGER_H

#include "common.h"

#ifndef NULL 
#define NULL ((void*) 0)
#endif


typedef struct FontBitMap{
	Region Region;  
	int iOriginX;
	int iOriginY;
	int iOriginNextX;
	int iOriginNextY;
	unsigned char *pucBuf;
}FontBitMap, *pFontBitMap;

typedef struct FontOpr{
	char *name;
	int (*Init)(char *FontFileName);
	int (*SetSize)(int size);
	int (*GetBuf)(unsigned int dwCode, pFontBitMap BitMap);
	struct FontOpr *pNext;
}FontOpr, *pFontOpr;

void InsertFontList(pFontOpr pNewFont);
void FreetypeRegister(void);
int FreetypeSetSize(int size);
int FreetypeGetBuf(unsigned int dwCode, pFontBitMap BitMap);

int SelectFont(char *FontName, char* FontFile);
void FontsRegister(void);
void SetFontSize(int FontSize);
void GetFontBitMap(unsigned int dwCode, pFontBitMap BitMap);

#endif

