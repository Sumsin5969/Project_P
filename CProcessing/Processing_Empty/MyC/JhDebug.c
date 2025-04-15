#include "JhDebug.h"
#include "cprocessing.h"
#include "cprocessing_common.h"
#include "ZoomCamera.h"
#include <stdio.h> 
#include "string.h"
#include "../unit.h"
#include "../Defines.h"
#include "../Player.h"

char buffer[200];
char playerPosX[200];
char playerPosY[200];
char playerSpeed[200];

char debugString[100][100];

int debugStringIndex;

float nowTime;
float nowFrameCount;
CP_Font my_awesome_font;

static PlayerCharacter* pc;

void InitDebuging()
{
	my_awesome_font = CP_Font_Load("Assets/Exo2-Regular.ttf");
	CP_Font_Set(my_awesome_font);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, CP_TEXT_ALIGN_V_TOP);
	CP_Settings_TextSize(36.f);

	nowTime = 0.f;
	nowFrameCount = 0.f;

	pc = GetPlayer();
}

void PrintFrameInfo()
{
	nowTime = CP_System_GetSeconds();
	nowFrameCount = (float)CP_System_GetFrameCount();

	sprintf_s(buffer, sizeof(buffer), "Time : %.2f", nowTime);
	CP_Font_DrawText(buffer, 0, 0);

	sprintf_s(buffer, sizeof(buffer), "frameCount : %.2f", nowFrameCount);
	CP_Font_DrawText(buffer, 0, 50);
}

void PrintPlayerInfo(struct PlayerCharacter* _pc)
{
	sprintf_s(buffer, sizeof(playerPosX), "X : %.2f", _pc->pos.x);
	CP_Font_DrawText(buffer, 500, 0);

	sprintf_s(buffer, sizeof(playerPosY), "Y : %.2f", _pc->pos.y);
	CP_Font_DrawText(buffer, 500, 50);

	sprintf_s(buffer, sizeof(playerSpeed), "Speed : %.2f", _pc->spd);
	CP_Font_DrawText(buffer, 500, 100);
	
	sprintf_s(buffer, sizeof(playerSpeed), "playerSize : %.5f", _pc->size * GetCamera()->camZoom);
	CP_Font_DrawText(buffer, 1000, 0);

	sprintf_s(buffer, sizeof(playerSpeed), "camzoomValue : %.5f", GetCamera()->camZoom);
	CP_Font_DrawText(buffer, 1000, 50);
}

void PrintFloat(int _Index,float _xPos, float _yPos, char* _string, float _value)
{
	sprintf_s(debugString[_Index], sizeof(debugString[_Index]), "%s : %.2f",_string, _value);

	CP_Font_DrawText(debugString[_Index], _xPos, _yPos);
}

void ZoomTest()
{
	if (CP_Input_KeyReleased(KEY_F3))
	{
		ZoomIn();
	}
	else if (CP_Input_KeyReleased(KEY_F4))
	{
		ZoomOut();
	}
}

void PlayerToZero()
{
	
}

void DebugUpdate()
{

	PrintFrameInfo();
	PrintPlayerInfo(pc);
	PrintFloat(0, WIDTH / 2, WIDTH / 2, "dashDecayRate", pc->dashDecayRate);

	PlayerToZero();
	ZoomTest();
}

