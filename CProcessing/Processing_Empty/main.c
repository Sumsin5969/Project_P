
#include <stdio.h>
#include "cprocessing.h"
#include "unit.h"
CP_Font font;

extern CP_Vector player_pos;
void game_init(void)
{
	font = CP_Font_Load("Assets/Exo2-Regular.ttf");
	SetPosition(1760, 990);
}

void game_update(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(50, 50, 50, 0));
	CP_System_SetFrameRate(100);
	DrawPlayer(player_pos.x, player_pos.y);
	PlayerMove();
	if (CP_Input_KeyDown(KEY_G)) InitChar();
	ChangeSpeed();
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_RIGHT, CP_TEXT_ALIGN_V_BOTTOM);
	//CP_Font_DrawText(player_pos.x, 0, 0);
	char buf[1];
	sprintf(buf, "%f", 3.14);
	printf("%s\n", buf);
}

void game_exit(void)
{

}

int main(void)
{
	CP_System_SetWindowSize(1760, 990);
	CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	CP_Engine_Run();
	return 0;
}