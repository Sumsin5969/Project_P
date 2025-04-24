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

	EnemyInit_StageOne(enemies[StageOne]);

	EnemyInit_StageTwo(enemies[StageTwo], Lasers_StageTwo);

	InitDebuging();

	SetWallType(wall);

	InitWall(wall);

	InitObstacle(obstacles);
}

void GMUpdate()
{
	CheckPlayerState();

	CheckGameState();

	StageTimer();

	if (gameState == Play)
	{
		PlayerMove();

		Dash();


		for (int i = 0; i < MAX_ENEMIES; i++)
		{
			EnemyMove_StageOne(&enemies[StageOne][i]);
			if (stageState > StageOne)
			{
				LaserAttack(&Lasers_StageTwo[i]);
			}
		}
		
		for (int i = 0; i < MAX_ENEMIES;i++)
		{
			BulletConditioner(&enemies[StageOne][i], Bullets_StageOne[i]);
			DirectBulletFire(&enemies[StageOne][i], Bullets_StageOne[i]);
		}

		for (int i = 0; i < MAX_ENEMIES; i++)
		{
			CheckBullet(Bullets_StageOne[i]);

			CheckWallBullet(wall, Bullets_StageOne[i]);
		}

		CheckWall(wall);
		CheckObstacle(&obstacles[0][0]);
	}
}

void GMLateUpdate()
{
	CP_Graphics_ClearBackground(CP_Color_Create(15, 15, 15, 0));

	RenderWall(wall);
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		RenderEnemy(&enemies[StageOne][i]);
		if (stageState > StageOne)
		{
			RenderEnemy(&enemies[StageTwo][i]);
		}
	}
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		for (int j = 0; j < MAX_BULLETS_PER_ENEMY; j++)
		{
			if (Bullets_StageOne[i][j].active)
			{
				RenderBullet(&Bullets_StageOne[i][j]);
			}
			if (CircleBullets[i][j].active)
			{
				RenderBullet(&CircleBullets[i][j]);
			}
		}
		if (stageState > StageOne)
		{
			RenderLaser(enemies[StageTwo], &Lasers_StageTwo[i]);
		}
	}



	RenderObstacle(&obstacles[0][0]);

	RenderPlayerShadow();

	RenderPlayer();

	DebugUpdate();
	if (CP_Input_KeyTriggered(KEY_A)) gameState = StageDown; // 게임스테이트 디버깅용
	if (CP_Input_KeyTriggered(KEY_S)) gameState = Play;

	if (CP_Input_KeyTriggered(KEY_Q)) SetStageTime(0.5f);
	if (CP_Input_KeyTriggered(KEY_W)) player->playerState = HIT;

	DefaultTimerUI();
}
// 바로 아래 FreeAll 작성 시 찾기 편하도록 동적할당 할 때마다 그 목록을 여기에 적겠음.
// cam, EnemyInit, 
void FreeAll()
{
	DestroyPlayer();
	DestroyCam();
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		//free(&CircleBullets[i]);
	}
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

void CheckGameState()
{
	switch (gameState)
	{
	case StageDown:
		printf("스테이지 다운!");
		StageTimerLevelDown();
		break;
	case StageUp:
		StageTimerLevelUp();
		break;
	default:
		break;
	}
}
void AllBulletInit(Bullet* _bullet);
void CheckPlayerState()
{
	switch (player->playerState)
	{
	case HIT:
		stageState--;

		PlayerInit();

		for (int i = 0; i < MAX_ENEMIES; i++)
		{
			AllBulletInit(Bullets_StageOne[i]);
		}

		if (stageState < StageOne)
		{
			StageTimerReset();
			gameState = GameOver;
			return;
		}

		SetZoomInTargetRate();

		player->playerState = NORMAL;

		gameState = StageDown;

		break;
	case NORMAL:
		break;

	case INVINCIBLE:
		break;

	}
}

void AllBulletInit(Bullet* _bullet)
{
	for (int i = 0; i < MAX_BULLETS_PER_ENEMY; i++)
	{
		_bullet[i].active = 0;
	}
}
void SavePlayerPos()
{
	pcShadow[shadowIndex] = player->pos;
	shadowIndex++;
}