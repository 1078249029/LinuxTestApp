#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <linux/fb.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include "input_manager.h"

int main(int argc, char **argv)
{
	int ret;
	
		printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	InputRegister();
	InputInit();
	InputEvent event;
	while (1)
	{
		ret = InputGetEvent(&event);
		
		if (ret) {
			printf("GetInputEvent err!\n");
			return -1;
		}
		else
		{
			if(event.iType == INPU_TYPE_TOUCH)
			{
				printf("iType: %d\n", event.iType);
				printf("iX		: %d\n", event.iX);
				printf("iY		: %d\n", event.iY);
			}
			if(event.iType == INPU_TYPE_NET)	
			{
				printf("iType   : %d\n", event.iType);
				printf("str		: %s\n", event.netstr);
			}
		}
	}
	
	return 0;	
}


