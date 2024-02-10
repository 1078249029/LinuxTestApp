#ifndef _CONFIG_H
#define _CONFIG_H

#include "common.h"

#define ItemCfgCountArrMAX 30
#define CFG_FILE "./include/config.h"

typedef struct ItemCfg{
	int index;
	char name;
	int canbetouched;
	char command[100];
}ItemCfg, *pItemCfg;

int GetItemCfgCount(void);
pItemCfg GetItemCfgByIndex(int index);
pItemCfg GetItemCfgByName(char *name);

#endif

