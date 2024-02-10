
#include <config.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>


static ItemCfg ItemCfgCountArr[ItemCfgCountArrMAX];
static int ItemCfgCount = 0;


int ParseCfgFile(char *strFilename)
{
	char *p;
	File *fd;
	char buf[100];
	fd = fopen(CFG_FILE, 'r');

	while(fgets(buf, 100, fd))
	{
		buf[99] = '\0';
		p = buf;
		while(*p == ' ' || *p == '\t')
			p++;
		if(*p == '#')
			continue;
		ItemCfgCountArr[ItemCfgCount].command[0] = '\0';
		ItemCfgCountArr[ItemCfgCount].index = ItemCfgCount;
		sscanf(p, "%s %d %s", ItemCfgCountArr[ItemCfgCount].name, ItemCfgCountArr[ItemCfgCount].canbetouched,
								ItemCfgCountArr[ItemCfgCount].command);
		ItemCfgCount++;
	}
	return 0;
}

int GetItemCfgCount(void)
{
	return ItemCfgCount;
}

pItemCfg GetItemCfgByIndex(int index)
{
	if(index < ItemCfgCount)
		return &ItemCfgCountArr[index];
	else
		return NULL;
}

pItemCfg GetItemCfgByName(char *name)
{
	int i,j;
	for(i = 0; i < ItemCfgCountArrMAX; i++)
	{
		if(!strcmp(ItemCfgCountArr[i].name, name))
			return &ItemCfgCountArr[i];
	}
	return NULL;
}

