#include "stdio.h"
#include "stdlib.h"
#include "GameManager.h"
#include "../Defines.h"
#include "ZoomCamera.h"
#include "PP_Renderer.h"
#include "JhDebug.h"
#include "Collision.h"
#include "../Enemy.h"
#include "../StageManager.h"

Obstacle wall[MAX];
Obstacle obstacles[7][2];

//Obstacle* obstacle;
//BossCharacter* boss;

void InitGameManager()
{
	InitCamera();

	PlayerInit();

	InitEnemies();

	InitDebuging();

	SetWallType(wall);

	InitWall(wall);

	InitObstacle(obstacles);
}

void GMUpdate()
{
	// 플레이어 -> 게임 -> 적 순으로 업데이트
	CheckPlayerState();

	CheckGameState();

	// 벽과 장애물 체크
	StageTimer();

	if (gameState == Play)
	{
		CheckWall(wall);

		//CheckObstacle(&obstacles[0][0]);

		PlayerMove();

		ChangeSize();
		
		Update_Enemy();

		Dash();
	}
}

void GMLateUpdate()
{
	CP_Graphics_ClearBackground(CP_Color_Create(15, 15, 15, 0));

	RenderAll();

	if (CP_Input_KeyTriggered(KEY_A)) gameState = StageDown; // 게임스테이트 디버깅용
	if (CP_Input_KeyTriggered(KEY_S)) gameState = Play;
	if (CP_Input_KeyTriggered(KEY_Q)) SetStageTime(0.5f);
	if (CP_Input_KeyTriggered(KEY_W)) player->playerState = HIT;
	if (CP_Input_KeyTriggered(KEY_G)) player->playerState = INVINCIBLE;
}

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
void CheckPlayerState()
{
	switch (player->playerState)
	{
	case HIT:
		stageState--;

		if (stageState < StageOne)
		{
			// x초간 연출 후 게임오버시키기
			InitAll();

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

void InitEnemies()
{
	EnemyInit_StageOne(enemies[StageOne]);
	EnemyInit_StageTwo(enemies[StageTwo], Lasers_StageTwo);
	EnemyInit_StageThree(enemies[StageThree]);
	EnemyInit_StageFour(enemies[StageFour]);
	EnemyInit_BossStage(&boss);
}

void InitAll()
{
	PlayerInit();
	StageTimerReset();
	InitWall(wall);
	InitEnemies();
}

void SavePlayerPos()
{
	pcShadow[shadowIndex] = player->pos;
	shadowIndex++;
}

// 스테이지1 업데이트 관리
void Update_StageOne()
{
	if (stageState >= StageOne)
	{
		for (int i = 0; i < MAX_ENEMIES;i++)
		{
			CheckEnemy(&enemies[StageOne][i]);
			EnemyMove_StageOne(&enemies[StageOne][i]);
		}
	}
}

// 스테이지2 업데이트 관리
void Update_StageTwo()
{
	if (stageState >= StageTwo)
	{
		for (int i = 0; i < MAX_ENEMIES; i++)
		{
			CheckEnemy(&enemies[StageTwo][i]);
			CreateLaser(&enemies[StageTwo][i], &Lasers_StageTwo[i]);
			CheckLaser(&Lasers_StageTwo[i]);
			LaserAttack(&Lasers_StageTwo[i]);
		}
	}
}

// 스테이지3 업데이트 관리
void Update_StageThree()
{
	if (stageState >= StageThree)
	{
		for (int i = 0; i < MAX_ENEMIES; i++)
		{
			CheckEnemy(&enemies[StageThree][i]);
			CircleBulletConditioner(&enemies[StageThree][i], CircleBullets_StageThree[i]);
			CircleBulletFire(&enemies[StageThree][i], CircleBullets_StageThree[i]);

			for (int j = 0; j < CLIP; j++)
			{
				CheckBullet(CircleBullets_StageThree[i][j]);

				CheckWallBullet(wall, CircleBullets_StageThree[i][j]);
			}
		}
	}
}

// 스테이지4 업데이트 관리
void Update_StageFour()
{
	if (stageState >= StageFour)
	{
		for (int i = 0; i < MAX_ENEMIES; i++)
		{
			CheckEnemy(&enemies[StageFour][i]);
			EnemyMove_StageFour(&enemies[StageFour][i]);
			BulletConditioner(&enemies[StageFour][i], Bullets_StageFour[i]);
			DirectBulletFire(&enemies[StageFour][i], Bullets_StageFour[i]);
			CheckBullet(Bullets_StageFour[i]);
			CheckWallBullet(wall, Bullets_StageFour[i]);
		}
	}
}

// 보스 스테이지 관리
void Update_StageBoss()
{
	if (stageState == StageBoss)
	{
		boss.active = 1;
	}
	if (boss.active == 1)
	{
		CheckBoss(&boss);
		EnableBoss(&boss);
	}
	else
	{
		DisableBoss(&boss);
	}
}

void Update_Enemy()
{
	Update_StageOne();
	Update_StageTwo();
	Update_StageThree();
	Update_StageFour();
	Update_StageBoss();
}