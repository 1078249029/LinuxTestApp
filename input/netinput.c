
#include "input_manager.h"
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>


#define SERVER_PORT 8888
static int iSocketServer;

static int NetInputGetInputEvent(pInputEvent pEvent)
{
	struct sockaddr_in tSocketClientAddr;
	static int iAddrLen;
	int iRecvLen;
	char ucRecvBuf[1000];

	iAddrLen = sizeof(struct sockaddr);
	iRecvLen = recvfrom(iSocketServer, ucRecvBuf, 999, 0, (struct sockaddr *)&tSocketClientAddr, (socklen_t *)&iAddrLen);
	if (iRecvLen > 0)
	{
		ucRecvBuf[iRecvLen] = '\0';
		pEvent->iType = INPU_TYPE_NET;
		gettimeofday(&pEvent->tTime, NULL);
		strncpy(pEvent->netstr, ucRecvBuf, 1000);
		pEvent->netstr[999] = '\0';
	}
	return 0;
}


static int NetInputDeviceInit(void)
{
	struct sockaddr_in tSocketServerAddr;
	int iRet;
	iSocketServer = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == iSocketServer)
	{
		printf("socket error!\n");
		return -1;
	}

	tSocketServerAddr.sin_family      = AF_INET;
	tSocketServerAddr.sin_port        = htons(SERVER_PORT);  /* host to net, short */
 	tSocketServerAddr.sin_addr.s_addr = INADDR_ANY;
	memset(tSocketServerAddr.sin_zero, 0, 8);
	
	iRet = bind(iSocketServer, (const struct sockaddr *)&tSocketServerAddr, sizeof(struct sockaddr));
	if (-1 == iRet)
	{
		printf("bind error!\n");
		return -1;
	}
	return 0;
}

static int NetInputDeviceExit(void)
{
	
	close(iSocketServer);
	return 0;
}

InputOpr NetInput = {
	.name = "NetInput",
	.GetInputEvent = NetInputGetInputEvent,
	.DeviceInit = NetInputDeviceInit,
	.DeviceExit = NetInputDeviceExit,	
};

void NetRegister(void)
{
	InputInsertList(&NetInput);
}


#if 0

int main(int argc, char **argv)
{
	InputEvent event;

	while(1)
	{
		NetInput.DeviceInit();
		NetInput.GetInputEvent(&event);
		printf("type %d\n", event.iType);
		printf("netstr %s\n", event.netstr);	
	}
	return 0;
}




#endif

