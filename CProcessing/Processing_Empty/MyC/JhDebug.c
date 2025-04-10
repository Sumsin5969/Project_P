#include "cprocessing.h"
#include <stdio.h> 
char buffer[200];
char buffer2[200];

float nowTime;
float nowFrameCount;
CP_Font my_awesome_font;

void InitDebuging()
{
	my_awesome_font = CP_Font_Load("Assets/Exo2-Regular.ttf");
	CP_Font_Set(my_awesome_font);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, CP_TEXT_ALIGN_V_TOP);
	CP_Settings_TextSize(36.f);

	nowTime = 0.f;
	nowFrameCount = 0.f;
}

void PrintFrameInfo()
{
	nowTime = CP_System_GetSeconds();
	nowFrameCount = (float)CP_System_GetFrameCount();

	sprintf_s(buffer, sizeof(buffer), "Time : %.2f", nowTime);
	CP_Font_DrawText(buffer, 0, 0);

	sprintf_s(buffer2, sizeof(buffer2), "frameCount : %.2f", nowFrameCount);
	CP_Font_DrawText(buffer2, 0, 50);
}