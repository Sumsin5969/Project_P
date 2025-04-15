#include "stdio.h"
#include "stdlib.h"
#include "ZoomCamera.h"
#include "PP_Renderer.h"
#include "../Defines.h"
#include "JhDebug.h"
#include "Collision.h"
#include "../Enemy.h"

PlayerCharacter* playerCharacter;
Enemy* enemyCharacter;
//Obstacle* obstacle;
//BossCharacter* boss;

void InitGameManager()
{
	PlayerInit();

	playerCharacter = GetPlayer();

	InitCamera();

	InitDebuging();
}

void GMUpdate()
{
	PlayerMove();
	Dash();
	CheckWall();
}

void GMLateUpdate()
{
	CP_Graphics_ClearBackground(CP_Color_Create(15, 15, 15, 0));

	RenderWall();

	RenderPlayer(playerCharacter);

	DebugUpdate();
}

void FreeAll()
{
	
}
