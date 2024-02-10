#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <linux/fb.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include "disp_manager.h"
#include "font_manager.h"

int main(int argc, char **argv)
{
	Region Region;  
	pDispBuff ptbuff;
	int font_size;
	if(argc != 2)
	{
		printf("Usage: %s <fontfile>\n",argv[0]);
		return -1;
	}

	DispInit();
	//SelectDisp("fb"); 我已经完成了，所以注释掉
	InitDefaultDisp();
	
	InputRegister();
	InputInit();
	
	FontsRegister();
	
	SelectFont("freetype", argv[1]);
	
	ptbuff = GetDispBuf();
	
	SetFontSize(font_size);
	
	return 0;	
}

