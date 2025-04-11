
#include <stdio.h>
#include "cprocessing.h"
#include "unit.h"
#include "./MyC/JhDebug.h"
#include "./MyC/Collision.h"
#define WIDTH 1760
#define HEIGHT 990
extern CP_Vector player_pos;

struct PlayerCharacter player;

void game_init(void)
{
	//font = CP_Font_Load("Assets/Exo2-Regular.ttf");
	InitChar(WIDTH, HEIGHT);
	InitDebuging();
}

void game_update(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(50, 50, 50, 0));
	CP_System_SetFrameRate(100);
	DrawPlayer(player.pos.x, player.pos.y);
	PlayerMove();
	if (CP_Input_KeyDown(KEY_G)) InitChar(WIDTH, HEIGHT);
	ChangeSpeed();

	PrintFrameInfo();

	PrintPlayerInfo(player);
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