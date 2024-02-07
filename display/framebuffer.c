
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <linux/fb.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>

#include "disp_manager.h"


static int fd_fb;
static struct fb_var_screeninfo var;	/* Current var */
static int screen_size;
static char *fb_base;
static unsigned int line_width;
static unsigned int pixel_width;


static int FBGetBuffer(pDispBuff pbuff)
{
	pbuff->pXres = var.xres;
	pbuff->pYres = var.yres;
	pbuff->pBpp = var.bits_per_pixel;
	pbuff->buff = fb_base;
	return 0;
}

static int FBFlushRegion(PRegion ptRegion, pDispBuff pbuff)
{	
	return 0;
}

static int FBDeviceInit(void)
{
	fd_fb = open("/dev/fb0", O_RDWR);
	if (fd_fb < 0)
	{
		printf("can't open /dev/fb0\n");
		return -1;
	}
	if (ioctl(fd_fb, FBIOGET_VSCREENINFO, &var))
	{
		printf("can't get var\n");
		return -1;
	}

	line_width  = var.xres * var.bits_per_pixel / 8;
	pixel_width = var.bits_per_pixel / 8;
	screen_size = var.xres * var.yres * var.bits_per_pixel / 8;
	fb_base = mmap(NULL , screen_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_fb, 0);
	if (fb_base == (char *)-1)
	{
		printf("can't mmap\n");
		return -1;
	}
	return 0;
}

static int FBDeviceExit(void)
{
	munmap(fb_base , screen_size);
	close(fd_fb);
	
	return 0;	
}


DispOpr FBDispOpr = {
	.name = "FBDispOpr",
	.DeviceInit = FBDeviceInit,
	.DeviceExit = FBDeviceExit,
	.GetBuffer = FBGetBuffer,
	.FlushRegion = FBFlushRegion,
};

void FBRegister(void)
{
	RegisteDisp(&FBDispOpr);
}



