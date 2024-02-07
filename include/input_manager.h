#ifndef _INPUT_MANAGER_H
#define _INPUT_MANAGER_H

#include <sys/time.h>

#ifndef NULL 
#define NULL ((void*) 0)
#endif


#define INPU_TYPE_TOUCH 1
#define INPU_TYPE_NET   2

typedef struct InputEvent{
	struct timeval tTime;
	int iType;
	int iX;
	int iY;
	int iClick;
	char netstr[1024];
}InputEvent, *pInputEvent;

typedef struct InputOpr{
	char *name;
	int (*GetInputEvent)(pInputEvent pEvent);
	int (*DeviceInit)(void);
	int (*DeviceExit)(void);
	struct InputOpr *pNext;
}InputOpr, *pInputOpr;

void TouchScreenRegister(void);
void NetRegister(void);
void InputInsertList(pInputOpr pInput);

void InputRegister(void);
int InputGetEvent(pInputEvent pevent);
int InputInit(void);
void *InputRecvThread (void *data);

#endif

