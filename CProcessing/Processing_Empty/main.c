
#include <stdio.h>
#include "cprocessing.h"
#include "./MyC/GameManager.h"
#include "unit.h"
#include "./MyC/Collision.h"
#include "Defines.h"

PlayerCharacter player;

void DrawWall()
{
	CP_Settings_Fill(CP_Color_Create(238, 1, 147, 255));
	CP_Settings_Stroke(CP_Color_Create(0,0,0, 0));
	// 왼쪽 벽
	CP_Graphics_DrawRect(WALLWIDTHSIZE/2, HEIGHT/2, WALLWIDTHSIZE, HEIGHT);
	// 오른쪽 벽
	CP_Graphics_DrawRect(WIDTH-(WALLWIDTHSIZE/2), HEIGHT / 2, WALLWIDTHSIZE, HEIGHT);
	// 위쪽 벽
	CP_Graphics_DrawRect(WIDTH/2, WALLHEIGHTSIZE/2, WIDTH, WALLHEIGHTSIZE);
	// 아래쪽 벽
	CP_Graphics_DrawRect(WIDTH/2, HEIGHT-(WALLHEIGHTSIZE/2), WIDTH, WALLHEIGHTSIZE);
}

void game_init(void)
{
	//font = CP_Font_Load("Assets/Exo2-Regular.ttf");
	InitChar(WIDTH, HEIGHT);
	//InitDebuging();
	InitGameManager();
	//PlayerInit();
}

void game_update(void)
{
	//CP_Graphics_ClearBackground(CP_Color_Create(15, 15, 15, 0));
	//DrawWall();
	//CP_System_SetFrameRate(100);
	//DrawPlayer(player.pos.x,  player.pos.y);
	//PlayerMove();
	//if (CP_Input_KeyDown(KEY_G)) InitChar(WIDTH, HEIGHT);
	//ChangeSpeed();
	//Dash();
	//CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	//PrintFrameInfo();
	//PrintPlayerInfo(player);
	//PrintFloat(0, WIDTH/2,WIDTH/2,"dashDecayRate",player.dashDecayRate);

	GMUpdate();

	GMLateUpdate();
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