
#include <stdio.h>
#include "cprocessing.h"
#include "unit.h"
#include "./MyC/JhDebug.h"

extern CP_Vector player_pos;

struct PlayerCharacter sumsin;

void game_init(void)
{
	//font = CP_Font_Load("Assets/Exo2-Regular.ttf");
	SetPosition(1760, 990);
	InitDebuging();

	sumsin.posX = 0;
	sumsin.posY = 50;
	sumsin.speed = 400;
}

void game_update(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(50, 50, 50, 0));
	CP_System_SetFrameRate(100);
	DrawPlayer(player_pos.x, player_pos.y);
	PlayerMove();
	if (CP_Input_KeyDown(KEY_G)) InitChar();
	ChangeSpeed();

	PrintFrameInfo();

	PrintPlayerInfo(sumsin);
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