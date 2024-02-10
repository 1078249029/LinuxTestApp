#ifndef _UI_H
#define _UI_H

#include "common.h"
#include "disp_manager.h"
#include "input_manager.h"

#define DEFAULT_BUTTON_COLOR 0xff0000
#define CLICK_BUTTON_COLOR 0x00ff00
#define DEFAULT_TEXT_COLOR 0x000000

struct Button;

typedef void (*DRAW)(struct Button *pbutton, pDispBuff pBuff);
typedef void (*CLICK)(struct Button *pbutton, pDispBuff pBuff, pInputEvent pEvent);

typedef struct Button{
	char *name;
	Region tRegion;
	CLICK Click;
	DRAW Draw;
}Button, *pButton;

void InitButton(pButton pbutton, char *name, PRegion pRegion, CLICK Click, DRAW Draw);

#endif

