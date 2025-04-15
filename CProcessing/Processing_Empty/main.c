
#include <stdio.h>
#include "cprocessing.h"
#include "./MyC/GameManager.h"
#include "unit.h"
#include "./MyC/Collision.h"
#include "Defines.h"


void game_init(void)
{
	InitGameManager();
}

void game_update(void)
{
	GMUpdate();
	GMLateUpdate();
}

void game_exit(void)
{
	FreeAll();
}

int main(void)
{
	CP_System_SetWindowSize(WIDTH, HEIGHT);
	CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	CP_Engine_Run();
	return 0;
}