#include <stdio.h>
#include "ui.h"
#include "page_manager.h"

static void MainPageRun(void *pParams)
{
	printf("MainPage Running!\n");
}

static PageAction PageOpr = {
	.name = "main", 
	.Run = MainPageRun,
};

void MainPageRegister(void)
{
	PageInsertList(&PageOpr);
}

