

#include "disp_manager.h"
#include <stdio.h>
#include <string.h>

/* 管理LCD还是网络 */
pDispOpr pDispNextHead = NULL;
static pDispOpr pDispNext = NULL;
static pDispOpr pDispCur = NULL;
DispBuff g_tbuff;
static int line_width;
static int pixel_width;

int PutPixel(int x, int y, unsigned int dwColor)
{
	unsigned char *pen_8 = (unsigned char *)(g_tbuff.buff+y*line_width+x*pixel_width);
	unsigned short *pen_16;	
	unsigned int *pen_32;	

	unsigned int red, green, blue;	

	pen_16 = (unsigned short *)pen_8;
	pen_32 = (unsigned int *)pen_8;

	switch (g_tbuff.pBpp)
	{
		case 8:
		{
			*pen_8 = dwColor;
			break;
		}
		case 16:
		{
			/* 565 */
			red   = (dwColor >> 16) & 0xff;
			green = (dwColor >> 8) & 0xff;
			blue  = (dwColor >> 0) & 0xff;
			dwColor = ((red >> 3) << 11) | ((green >> 2) << 5) | (blue >> 3);
			*pen_16 = dwColor;
			break;
		}
		case 32:
		{
			*pen_32 = dwColor;
			break;
		}
		default:
		{
			printf("can't surport %dbpp\n", g_tbuff.pBpp);
			break;
		}
	}
	return 0;
}

int DispFlushRegion(PRegion ptRegion, pDispBuff pbuff)
{
	pDispCur->FlushRegion(ptRegion, pbuff);
	return 0;
}

pDispBuff GetDispBuf(void)
{
	return &g_tbuff;
}


void RegisteDisp(pDispOpr ptemp)
{
//	if(!pDispNextHead)
//	{
//		pDispNext = pDispNextHead;
//		pDispCur = pDispNextHead;
//	}
//	pDispNext->pNext = ptemp;
//	pDispNext = pDispNext->pNext;
//	pDispNext->pNext = NULL;
	ptemp->pNext = pDispNext;
	pDispNext = ptemp;
}

void DispInit(void)
{
	FBRegister();	
}

int SelectDisp(char *name)
{
	while(1)
	{
		if(!strcmp(pDispNext->name, name))
		{
			pDispCur = pDispNext;
			return 0;
		}
		if(pDispNext->pNext == NULL)
		{
			return -1;
		}
		pDispNext = pDispNext->pNext;
	}
}

int InitDefaultDisp(void)
{
	SelectDisp("FBDispOpr");
	pDispCur->DeviceInit();
	pDispCur->GetBuffer(&g_tbuff);
	
	line_width = g_tbuff.pXres * g_tbuff.pBpp/8;
	pixel_width = g_tbuff.pBpp/8;
	return 0;
}


