#include "stdio.h"
#include "stdlib.h"
#include "ZoomCamera.h"
#include "PP_Renderer.h"
#include "../Defines.h"
#include "JhDebug.h"
#include "Collision.h"
#include "../Enemy.h"
#include "../Obstacle.h"
#include "../StageManager.h"

Obstacle wall[MAX];
//Obstacle* obstacle;
//BossCharacter* boss;

PlayerState playerState;
StageState stageState;
GameState gameState;

void InitGameManager()
{
	InitCamera();

	PlayerInit();

	EnemyInit();

	InitDebuging();

	SetWallType(wall);
	InitWall(wall);
}

void GMUpdate()
{
	PlayerMove();
	Dash();
	CheckWall(&wall[0]);
}

void GMLateUpdate()
{
	CP_Graphics_ClearBackground(CP_Color_Create(15, 15, 15, 0));

	LaserAttack();
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		CircleBulletFire(&enemies[i], allBullets[i]);
	}

	RenderWall(wall);

	RenderEnemy();

	RenderPlayer();

	DebugUpdate();
	if (CP_Input_KeyTriggered(KEY_A)) gameState = ChangingStage; // 게임스테이트 디버깅용
	if (CP_Input_KeyTriggered(KEY_S)) gameState = Play;
	StageTimer();
}
// 바로 아래 FreeAll 작성 시 찾기 편하도록 동적할당 할 때마다 그 목록을 여기에 적겠음.
// cam, EnemyInit, 
void FreeAll()
{
	DestroyPlayer();
	DestroyCam();
}

PlayerState GetPlayerState()
{
	return playerState;
}

StageState GetStageState()
{
	return stageState;
}

GameState GetGameState()
{
	return gameState;
}