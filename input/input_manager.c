
#include "input_manager.h"
#include <tslib.h>
#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>

#define BUF_LEN 20

pInputOpr pInputHead = NULL;

static int iread = 0;
static int iwrite = 0;
static InputEvent InputEventbuf[BUF_LEN];

static pthread_mutex_t g_tMutex  = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t  g_tConVar = PTHREAD_COND_INITIALIZER;


static int DataEmpty(void)
{
	return(iread == iwrite);
}

static int DataFull(void)
{
	return(iread == ((iwrite + 1) % BUF_LEN));
}

static int GetEventBuf(pInputEvent pEvent)
{
	if(!DataEmpty())
	{
		*pEvent = InputEventbuf[iread];
		iread = (iread + 1) % BUF_LEN; 
		return 1;
	}
	else
	{
		return 0;
	}
}

static int PutEventBuf(pInputEvent pEvent)
{
	if(!DataFull())
	{
		InputEventbuf[iwrite] = *pEvent;
		iwrite = (iwrite + 1) % BUF_LEN; 
		return 1;
	}
	else
	{
		return 0;
	}
}

void InputRegister(void)
{
	extern void TouchScreenRegister(void);
	TouchScreenRegister();
	extern void NetRegister(void);
	NetRegister();
}

void InputInsertList(pInputOpr pInput)
{
	pInput->pNext = pInputHead;
	pInputHead = pInput;
}

int InputGetEvent(pInputEvent pevent)
{
	InputEvent event;
	int ret;
	pthread_mutex_lock(&g_tMutex);
	if(GetEventBuf(&event))
	{
		*pevent = event;
		pthread_mutex_unlock(&g_tMutex);
		return 0;
	}
	else
	{
		pthread_cond_wait(&g_tConVar, &g_tMutex);	
		if(GetEventBuf(&event))
		{
			*pevent = event;
			ret = 0;
		}
		else
		{
			ret = -1;
		}
		pthread_mutex_unlock(&g_tMutex);
	}
	return ret;
}

void* InputRecvThread (void *data)
{
	pInputOpr pInputopr = (pInputOpr)data;
	InputEvent Event;
	int ret;
	while (1)
	{
		ret = pInputopr->GetInputEvent(&Event);
		if(!ret)
		{
			pthread_mutex_lock(&g_tMutex);
			
			PutEventBuf(&Event);
			
			pthread_cond_signal(&g_tConVar); 
			pthread_mutex_unlock(&g_tMutex);
		}
	}
	return NULL;
}


int InputInit(void)
{
	int ret;
	
	pInputOpr ptemp = pInputHead;
	while (ptemp)
	{
		pthread_t tid;
		ret = ptemp->DeviceInit();

		/* pthread creat */
		if(!ret)
		{
			ret = pthread_create(&tid, NULL, InputRecvThread, ptemp);
			if (ret)
			{
				printf("pthread_create err!\n");
				return -1;
			}
		}
		ptemp = ptemp->pNext;
	}
	return 0;
}




