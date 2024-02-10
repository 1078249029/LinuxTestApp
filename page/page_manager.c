#include <string.h>
#include "ui.h"
#include "page_manager.h"
#include "common.h"

static pPageAction PageCur = NULL;

void PageInsertList(pPageAction pPageOpr)
{
	pPageOpr->pNext = PageCur;
	PageCur = pPageOpr;
}

pPageAction GetPage(char *name)
{
	pPageAction pPageTemp = PageCur;
	while(pPageTemp)
	{
		if(!strcmp(pPageTemp->name, name))
		{
			return pPageTemp;
		}
		pPageTemp = pPageTemp->pNext;
	}
	return NULL;
}


void RegisterPage(void)
{
	MainPageRegister();
}
