#include "stdio.h"
#include "stdlib.h"
#include "../Defines.h"
#include "GameManager.h"
#include "ZoomCamera.h"
#include "PP_Renderer.h"
#include "JhDebug.h"
#include "Collision.h"
#include "../Enemy.h"
#include "../Obstacle.h"
#include "../StageManager.h"
Obstacle wall[MAX];
Obstacle obstacles[7][2];

Enemy enemy_1Stage[4];
Enemy enemy_2Stage[5];
Enemy enemy_3Stage[4];
Enemy enemy_4Stage[4];

Bullet bullet_1Stage[12];
Bullet bullet_2Stage[15];
Bullet bullet_3Stage[12];
Bullet bullet_4Stage[12];


//Obstacle* obstacle;
//BossCharacter* boss;

void InitGameManager()
{
	InitCamera();

	PlayerInit();

	EnemyInit();

	InitDebuging();

	SetWallType(wall);

	InitWall(wall);

	InitObstacle(obstacles);
}

void GMUpdate()
{
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		EnemyMove(&enemies[i]);
	}
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
		DirectBulletFire(&enemies[i], &PDBullets[i]);
	}

	RenderWall(wall);
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		RenderEnemy(&enemies[i]);
	}

	//RenderObstacle(obstacles);

	RenderPlayer();

	DebugUpdate();
	if (CP_Input_KeyTriggered(KEY_A)) gameState = StageDown; // 게임스테이트 디버깅용
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

float GetDt()
{
	return CP_System_GetDt();
}

PlayerState GetPlayerState()
{
	return player->playerState;
}

StageState GetStageState()
{
	return stageState;
}

GameState GetGameState()
{
	return gameState;
}

void SetGameState(GameState targetGameState)
{
	gameState = targetGameState;
}

