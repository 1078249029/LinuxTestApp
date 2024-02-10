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

#include <page_manager.h>
#include <font_manager.h>
#include <ui.h>

int main(int argc, char **argv)
{
	RegisterPage();
	GetPage("main")->Run(NULL);
	return 0;	
}


