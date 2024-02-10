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
#include "ui.h"


#define FONTDATAMAX 4096

int main(int argc, char **argv)
{
	Region Region;  
	pDispBuff ptbuff;
	
	if(argc != 2)
	{
		printf("Usage: %s <fontsize>\n",argv[0]);
		return -1;
	}

	DispInit();
	//SelectDisp("fb");
	InitDefaultDisp();
	
	FontsRegister();
	
	SelectFont("freetype", argv[1]);
	
	ptbuff = GetDispBuf();
	Button button;
	Region.iLeftUpX = 100;
	Region.iLeftUpY = 100;
	Region.iHeigh = 200;
	Region.iWidth = 200;
	InitButton(&button, "test", &Region, NULL, NULL);
	button.Draw(&button, ptbuff);
	while(1)
	{
		button.Click(&button, ptbuff, NULL);
		sleep(2);
	}
	return 0;	
}


