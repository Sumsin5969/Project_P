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
#include "../SoundManager.h"
#include "../BossStage.h"
#include "../TutorialStage.h"

Obstacle wall[MAX];
Obstacle obstacles[7][2];
Obstacle bosswall[11];
Obstacle tutorialwall[3];
Obstacle startbox[2];

CP_Image tutorialImage;
CP_Image endingImage;

void InitGameManager()
{
	InitTutorialObstacle(tutorialwall);
	InitStartBox(startbox);

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

	if (gameState == Play)
	{
		Update_Tutorial();

		CheckWall(wall);

		PlayerMove();

		Dash();

		ChangePlayerSize();

		if (stageState > Tutorial)
		{
			Update_Enemy();

			StageTimer();

			ChangeEnemySize();
		}
	}
	else if (gameState == GameClear)
	{
		Ending(&boss);
	}
}

void GMLateUpdate()
{
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 0));

	if (gameState == GameClear)
	{
		RenderPlayer();
		DrawEndingImage((GetCamera()->camZoom) / 44, (GetCamera()->camZoom) / 44);
		return;
	}

	if (stageState == Tutorial)
	{
		CP_Image_Draw(tutorialImage, GetCamera()->camPos.x, GetCamera()->camPos.y, 1760, 990, 255);
	}

	RenderAll();

	DebugUpdate();

	UpdateCameraShake();

	if (CP_Input_KeyTriggered(KEY_ESCAPE))
	{
		if (GetGameState() != Pause)
		{
			preGameState = GetGameState();
			SetGameState(Pause);
			CP_Sound_PauseAll();
		}
		else if (GetGameState() == Pause)
		{
			SetGameState(preGameState);
			CP_Sound_ResumeAll();
		}
	}
	if (CP_Input_KeyTriggered(KEY_A)) gameState = StageDown; // 게임스테이트 디버깅용
	if (CP_Input_KeyTriggered(KEY_S)) gameState = Play;
	if (CP_Input_KeyTriggered(KEY_Q)) SetStageTime(0.5f);
	if (CP_Input_KeyTriggered(KEY_W))
	{
		player->playerState = HIT;
	}
	if (CP_Input_KeyTriggered(KEY_G)) player->playerState = INVINCIBLE;
	if (CP_Input_KeyTriggered(KEY_Z)) EnemyInit_StageFive(&elite_StageFive);
	if (CP_Input_KeyTriggered(KEY_M)) CP_Sound_Play(titleBGM);
	if (CP_Input_KeyTriggered(KEY_O))
	{

		stageState = StageBoss;
		player->playerState = INVINCIBLE;

		SetZoom(stageState);

		/*	player->pos.x = 29500;

			boss.time = 80;*/
	}
}

void FreeAll()
{
	DestroyPlayer();
	DestroyCam();
}

float GetDt()
{
	float dt = CP_System_GetDt();
	if (CP_Input_KeyDown(KEY_2)) dt *= 2;
	if (CP_Input_KeyDown(KEY_3)) dt *= 3;
	if (CP_Input_KeyDown(KEY_4)) dt *= 4;
	if (CP_Input_KeyDown(KEY_5)) dt *= 5;
	return dt;
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
		SetZoomInTargetRate();

		player->playerState = NORMAL;

		SetGameState(StageDown);

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
	EnemyInit_StageFive(&elite_StageFive);
	EnemyInit_StageSix(&enemy_StageSix);
	InitBoss(&boss);
	InitBossFirstLaserShooter(BossFirstLaserShooter);
	InitBossFirstLaser(BossFirstLaserShooter, FirstLasers_BossStage);
	InitBossCrossBullet(&boss);
	InitPhaseThreeObstacle(bosswall);
	InitBossSpiralBullet(&boss);
	InitBossSecondLaserShooter(BossSecondLaserShooter);
	InitBossSecondLaser(BossSecondLaserShooter, SecondLasers_BossStage);
	InitBossThirdLaserShooter(BossThirdLaserShooter);
	InitBossThirdLaser(BossThirdLaserShooter, ThirdLasers_BossStage);
}


void InitAll()
{
	PlayerInit();
	StageTimerReset();
	InitWall(wall);
	InitTutorialObstacle(tutorialwall);
	InitStartBox(startbox);
	InitEnemies();
	InitCamPosition();
}

void SavePlayerPos()
{
	pcShadow[shadowIndex] = player->pos;
	shadowIndex++;
}

void SaveEnemyPos()
{
	enemyShadow[enemyShadowIndex] = elite_StageFive.pos;
	enemyShadowIndex++;
}

// 튜토리얼 스테이지 업데이트 관리
void Update_Tutorial()
{
	if (stageState == Tutorial)
	{
		CheckStartBox(&startbox[0]);
		for (int i = 0; i < 3; i++)
		{
			CheckObstacle(&tutorialwall[i]);
		}
	}
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
			BulletConditioner(&enemies[StageOne][i], Bullets_StageOne[i]);
			DirectBulletFire(&enemies[StageOne][i], Bullets_StageOne[i]);
			CheckBullet(Bullets_StageOne[i]);
			CheckWallBullet(wall, Bullets_StageOne[i]);
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
		}
	}
}

void Update_StageFive()
{
	if (stageState >= StageFive)
	{
		CheckBoss(&elite_StageFive);
		EnemyMove_StageFive(&elite_StageFive);
	}
}

void Update_StageSix()
{
	if (stageState >= StageSix)
	{
		CheckEnemy(&enemy_StageSix);
		EnemyMove_StageSix(&enemy_StageSix);
		BulletConditioner(&enemy_StageSix, Bullets_StageSix);
		DirectBulletFire(&enemy_StageSix, Bullets_StageSix);
		CheckBullet(Bullets_StageSix);
		CheckWallBullet(wall, Bullets_StageSix);
	}
}

// 보스 스테이지 관리
void Update_StageBoss()
{
	if (stageState == StageBoss)
	{
		CheckBoss(&boss);
		BossStageController(&boss);
	}
}

void Update_Enemy()
{
	switch (stageState)
	{
	case StageBoss:   Update_StageBoss();
		break;
	case StageSix:    Update_StageSix();
	case StageFive:   Update_StageFive();
	case StageFour:   Update_StageFour();
	case StageThree:  Update_StageThree();
	case StageTwo:    Update_StageTwo();
	case StageOne:    Update_StageOne();
		break;
	default:
		break;
	}
}

void SetTutorialImage(CP_Image img)
{
	tutorialImage = img;
}

void SetEndingImage(CP_Image img)
{
	endingImage = img;
}

void DrawEndingImage(float width, float height)
{
	float w = CP_Image_GetWidth(endingImage) * width;
	float h = CP_Image_GetHeight(endingImage) * height;


	if (WIDTH <= width) width = WIDTH;
	if (HEIGHT <= width) width = HEIGHT;

	CP_Image_Draw(endingImage, WIDTH / 2, HEIGHT / 2, w, h, 255);
}