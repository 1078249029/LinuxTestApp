
#include "ui.h"
#include "input_manager.h"
#include "disp_manager.h"

static int flag = 0;

static void DefalutClick(pButton pbutton, pDispBuff pbuff, pInputEvent pEvent)
{
	if(flag)
	{
		DrawRegion(&(pbutton->tRegion), CLICK_BUTTON_COLOR);
		DrawTextRegion(pbutton->name, &pbutton->tRegion, pbuff, DEFAULT_TEXT_COLOR);
		DispFlushRegion(&pbutton->tRegion, pbuff);
	}
	else
	{
		DrawRegion(&(pbutton->tRegion), DEFAULT_BUTTON_COLOR);
		DrawTextRegion(pbutton->name, &pbutton->tRegion, pbuff, DEFAULT_TEXT_COLOR);
		DispFlushRegion(&pbutton->tRegion, pbuff);

	}
	flag = !flag;
}

static void DefalutDraw(pButton pbutton, pDispBuff pbuff)
{
	DrawRegion(&(pbutton->tRegion), DEFAULT_BUTTON_COLOR);
	DrawTextRegion(pbutton->name, &pbutton->tRegion, pbuff, DEFAULT_TEXT_COLOR);
	DispFlushRegion(&pbutton->tRegion, pbuff);
}

void InitButton(pButton pbutton, char *name, PRegion pRegion, CLICK Click, DRAW Draw)
{
	pbutton->name = name;
	pbutton->tRegion = *pRegion;
	pbutton->Click = Click ? Click : DefalutClick;
 	pbutton->Draw = Draw ? Draw : DefalutDraw;
}

