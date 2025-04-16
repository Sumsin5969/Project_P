#include "stdio.h"
#include "stdlib.h"
#include "ZoomCamera.h"
#include "PP_Renderer.h"
#include "../Defines.h"
#include "JhDebug.h"
#include "Collision.h"
#include "../Enemy.h"
#include "../Obstacle.h"
PlayerCharacter* playerCharacter;
Enemy* enemyCharacter;
Obstacle wall[MAX];
//Obstacle* obstacle;
//BossCharacter* boss;

PlayerState playerState;



void InitGameManager()
{
	PlayerInit();

	playerState = NORMAL;

	playerCharacter = GetPlayer();

	InitCamera();

	InitDebuging();

	InitWall(&wall[0], LEFT);
	InitWall(&wall[1], RIGHT);
	InitWall(&wall[2], TOP);
	InitWall(&wall[3], BOTTOM);

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

	EnemyLaserAttack();

	RenderWall(wall);

	RenderPlayer(playerCharacter);


	DebugUpdate();
}

void FreeAll()
{
	
}
