#ifndef _PAGE_MANAGER_H
#define _PAGE_MANAGER_H

#ifndef NULL 
#define NULL ((void*) 0)
#endif

typedef struct PageAction{
	char *name;
	void (*Run)(void *pParams);
	struct PageAction *pNext;
}PageAction, *pPageAction;

void PageInsertList(pPageAction pPageOpr);
void MainPageRegister(void);
void RegisterPage(void);
pPageAction GetPage(char *name);

#endif

