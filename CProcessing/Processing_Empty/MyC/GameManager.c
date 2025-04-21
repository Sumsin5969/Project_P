#include "stdio.h"
#include "stdlib.h"
#include "GameManager.h"
#include "../Defines.h"
#include "ZoomCamera.h"
#include "PP_Renderer.h"
#include "JhDebug.h"
#include "Collision.h"
#include "../Enemy.h"
#include "../Obstacle.h"
#include "../StageManager.h"
Obstacle wall[MAX];
Obstacle obstacles[7][2];

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

	CheckPlayerState();

	CheckGameState();

	if (gameState == Play)
	{
		PlayerMove();
		Dash();
		CheckWall(&wall[0]);
	}
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

	//RenderEnemy();

	//RenderObstacle(obstacles);

	RenderPlayer();

	DebugUpdate();
	if (CP_Input_KeyTriggered(KEY_A)) gameState = StageDown; // 게임스테이트 디버깅용
	if (CP_Input_KeyTriggered(KEY_S)) gameState = Play;

	if (CP_Input_KeyTriggered(KEY_Q)) SetStageTime(3);
	if (CP_Input_KeyTriggered(KEY_W)) player->playerState = HIT;


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

void CheckGameState()
{
	switch (gameState)
	{
	case StageDown:
		StageTimer();
		break;
	case StageUp:
		ZoomOut();
		stageState++;
		gameState = Play;
		SetStageTime(30);
		break;
	default:
		break;
	}
}

void CheckPlayerState()
{
	switch (player->playerState)
	{
	case HIT:
		if (stageState == StageOne)
		{
			gameState = GameOver;
		}

		gameState = StageDown;
		break;
	case NORMAL:
		break;

	case INVINCIBLE:
		break;

	}
}