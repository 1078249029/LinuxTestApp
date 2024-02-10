
#include "font_manager.h"
#include <stdio.h>
#include <string.h>

static pFontOpr pFontDefault = NULL;
static pFontOpr pFontCur = NULL;


void InsertFontList(pFontOpr pNewFont)
{
	pNewFont->pNext = pFontCur;
	pFontCur = pNewFont;
}

int SelectFont(char *FontName, char* FontFile)
{
	pFontOpr ptemp;
	ptemp = pFontCur;
	while(ptemp)
	{
		if(!strcmp(ptemp->name, FontName))
		{
			break;
		}
		else
		{
			ptemp = ptemp->pNext;
		}
	}
	
	if(ptemp == NULL)
	{
		pFontDefault->Init("FontFile");
		printf("Default font freetype selected\n");
		return -1;
	}

	pFontDefault = ptemp;
	pFontDefault->Init(FontFile);
	return 0;
}

void FontsRegister(void)
{
	extern void FreetypeRegister(void);
	FreetypeRegister();
}

void SetFontSize(int FontSize)
{
	pFontDefault->SetSize(FontSize);
}

void GetFontBitMap(unsigned int dwCode, pFontBitMap BitMap)
{
	pFontDefault->GetBuf(dwCode, BitMap);
}

