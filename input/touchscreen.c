
#include "input_manager.h"
#include <tslib.h>
#include <sys/time.h>
#include <stdio.h>

static struct tsdev *g_ts;

static int TouchScreenGetInputEvent(pInputEvent pEvent)
{
	struct ts_sample samp;

	ts_read(g_ts, &samp, 1);
	pEvent->iType = INPU_TYPE_TOUCH;
	pEvent->iX = samp.x;	
	pEvent->iY = samp.y;
	pEvent->tTime = samp.tv;
	pEvent->iClick = samp.pressure;
	return 0;
}


static int TouchScreenDeviceInit(void)
{
	g_ts = ts_setup(NULL, 0);
	if (!g_ts)
	{
		printf("ts_setup err\n");
		return -1;
	}
	
	return 0;
}

static int TouchScreenDeviceExit(void)
{
	ts_close(g_ts);
	return 0;
}

InputOpr TouchScreen = {
	.name = "TouchScreen",
	.GetInputEvent = TouchScreenGetInputEvent,
	.DeviceInit = TouchScreenDeviceInit,
	.DeviceExit = TouchScreenDeviceExit,	
};

void TouchScreenRegister(void)
{
	InputInsertList(&TouchScreen);
}

#if 0

int main(int argc, char **argv)
{
	InputEvent event;

	TouchScreen.DeviceInit();
	TouchScreen.GetInputEvent(&event);
	printf("type %d\n", event.iType);
	printf("iClick %d\n", event.iClick);
	printf("iX %d\n", event.iX);
	printf("iY %d\n", event.iY);
	return 0;
}

#endif

