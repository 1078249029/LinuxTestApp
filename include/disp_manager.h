#ifndef _DISP_MANAGER_H
#define _DISP_MANAGER_H

#ifndef NULL 
#define NULL ((void*) 0)
#endif

typedef struct DispBuff{
	int pXres;
	int pYres;
	int pBpp;
	char *buff;
}DispBuff, *pDispBuff;

typedef struct  Region{
	int iLeftUpX;
	int iLeftUpY;
	int iWidth;
	int iHeigh;
}Region, *PRegion;

typedef struct DispOpr{
	char *name;
	int (*DeviceInit)(void);
	int (*DeviceExit)(void);
	int (*GetBuffer)(pDispBuff buff);
	int (*FlushRegion)(PRegion ptRegion, pDispBuff pbuff);
	struct DispOpr *pNext;
}DispOpr, *pDispOpr;

void FBRegister(void);
void DispInit(void);
void RegisteDisp(pDispOpr ptemp);
int InitDefaultDisp(void);
int DispFlushRegion(PRegion ptRegion, pDispBuff pbuff);
int PutPixel(int x, int y, unsigned int dwColor);
pDispBuff GetDispBuf(void);


#endif

