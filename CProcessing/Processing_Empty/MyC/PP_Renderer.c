#include "cprocessing.h"
#include "PP_Renderer.h"
#include "ZoomCamera.h"
#include "../Defines.h"
#include "stdio.h"
#include "GameManager.h"
#include <math.h>
#include "Collision.h"
#include "JhDebug.h"
#include "../StageManager.h"
#include "../Enemy.h"

int invincibleColorIndex = 0;


void RenderWall(Obstacle* _obstacles)
{
	CP_Settings_Fill(CP_Color_Create(200, 1, 147, 255));
	CP_Settings_NoStroke();

	for (int i = 0; i < MAX; ++i)
	{
		if (_obstacles->sniper == 1) CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255)); // 플레이어를 맞췄다면
		else CP_Settings_Fill(ENEMY_COLOR());
		CP_Graphics_DrawRect(_obstacles[i].pos.x, _obstacles[i].pos.y, _obstacles[i].width, _obstacles[i].height);
	}
}

void RenderPlayerShadow()
{
	CamInfo* cam = GetCamera();
	CP_Matrix camS = CP_Matrix_Scale(CP_Vector_Set(cam->camZoom, cam->camZoom));
	CP_Matrix camT = CP_Matrix_Translate(cam->camPos);
	CP_Matrix camMatrix = CP_Matrix_Multiply(camT, camS);

	int count = shadowIndex > 10 ? 10 : shadowIndex;  // 최대 잔상 수 제한

	for (int i = 0; i < count; ++i)
	{
		int idx = (shadowIndex - i - 1 + 100) % 100;  // 최근 위치부터 역순으로 가져오기

		CP_Vector target = CP_Vector_MatrixMultiply(camMatrix, pcShadow[idx]);
		float alpha = 150.f - (i * 12);  // 뒤로 갈수록 투명해짐

		if (alpha < 0) alpha = 0;

		switch (invincibleColorIndex % 6)
		{
		case 0:
			CP_Settings_Fill(CP_Color_Create(235, 219, 0, (int)alpha));
			break;
		case 1:
			CP_Settings_Fill(CP_Color_Create(235, 219, 0, (int)alpha));
			break;
		case 2:
			CP_Settings_Fill(CP_Color_Create(235, 190, 1, (int)alpha));
			break;
		case 3:
			CP_Settings_Fill(CP_Color_Create(235, 190, 1, (int)alpha));
			break;
		case 4:
			CP_Settings_Fill(CP_Color_Create(0, 235, 4, (int)alpha));
			break;
		case 5:
			CP_Settings_Fill(CP_Color_Create(0, 235, 4, (int)alpha));
			break;
		}

		CP_Graphics_DrawCircle(target.x, target.y, cam->camZoom * player->size);
	}
}

void RenderPlayer()
{
	CamInfo* cam = GetCamera();

	//CP_Vector baseV = CP_Vector_Set(WIDTH / 2 - _playerCharacter->pos.x, HEIGHT / 2 - _playerCharacter->pos.y);

	CP_Matrix pcS;
	pcS = CP_Matrix_Scale(CP_Vector_Set(cam->camZoom, cam->camZoom));
	CP_Matrix pcT;
	pcT = CP_Matrix_Translate(cam->camPos);

	CP_Matrix camMatrix = CP_Matrix_Multiply(pcT, pcS);

	CP_Vector targetVector = CP_Vector_MatrixMultiply(camMatrix, player->pos);

	if (player->playerState == INVINCIBLE)
	{
		switch (invincibleColorIndex % 6)
		{
		case 0:
			CP_Settings_Fill(CP_Color_Create(235, 219, 0, 255));
			break;
		case 1:
			CP_Settings_Fill(CP_Color_Create(235, 219, 0, 255));
			break;
		case 2:
			CP_Settings_Fill(CP_Color_Create(235, 190, 1, 255));
			break;
		case 3:
			CP_Settings_Fill(CP_Color_Create(235, 190, 1, 255));
			break;
		case 4:
			CP_Settings_Fill(CP_Color_Create(0, 235, 4, 255));
			break;
		case 5:
			CP_Settings_Fill(CP_Color_Create(0, 235, 4, 255));
			break;
		}
		invincibleColorIndex++;

		if (100 < invincibleColorIndex) invincibleColorIndex = 0;
		
		CP_Graphics_DrawCircle(targetVector.x, targetVector.y, cam->camZoom * player->size);
		CP_Settings_Fill(CP_Color_Create(36, 235, 238, 255));

		return;
	}
	CP_Settings_Fill(CP_Color_Create(36, 235, 238, 255));
	CP_Graphics_DrawCircle(targetVector.x, targetVector.y, cam->camZoom * player->size);
	if (!player->isDashing)
	{
		CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 255));
		CP_Settings_StrokeWeight(2.f * cam->camZoom);
		CP_Settings_Fill(CP_Color_Create(36, 235, 50, 255));
		CP_Graphics_DrawCircle(targetVector.x, targetVector.y, cam->camZoom * (player->size / 2.f));
	}
}


void RenderEnemy(Enemy* _enemy)
{
	CamInfo* cam = GetCamera();
	CP_Matrix camS = CP_Matrix_Scale(CP_Vector_Set(cam->camZoom, cam->camZoom));
	CP_Matrix camT = CP_Matrix_Translate(cam->camPos);
	CP_Matrix camMatrix = CP_Matrix_Multiply(camT, camS);
	CP_Vector targetVector = CP_Vector_MatrixMultiply(camMatrix, _enemy->pos);

	float _enemySize = _enemy->size * cam->camZoom;

	if (_enemy->sniper == 1) CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	else CP_Settings_Fill(ENEMY_COLOR());

	CP_Graphics_DrawRect(targetVector.x, targetVector.y, _enemySize, _enemySize);
}

void RenderBullet(Bullet* _bullet)
{
	CamInfo* cam = GetCamera();
	CP_Matrix camS = CP_Matrix_Scale(CP_Vector_Set(cam->camZoom, cam->camZoom));
	CP_Matrix camT = CP_Matrix_Translate(cam->camPos);
	CP_Matrix camMatrix = CP_Matrix_Multiply(camT, camS);
	CP_Vector targetVector = CP_Vector_MatrixMultiply(camMatrix, _bullet->projPos);

	float _bulletSize = _bullet->size * cam->camZoom;

	if (_bullet->sniper == 1) CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	else CP_Settings_Fill(ENEMY_COLOR());
	CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 255));

	CP_Graphics_DrawCircle(targetVector.x, targetVector.y, _bulletSize);
}

void RenderObstacle(Obstacle* _obstacle)
{
	CamInfo* cam = GetCamera();
	CP_Matrix camS = CP_Matrix_Scale(CP_Vector_Set(cam->camZoom, cam->camZoom));
	CP_Matrix camT = CP_Matrix_Translate(cam->camPos);
	CP_Matrix camMatrix = CP_Matrix_Multiply(camT, camS);
	CP_Vector targetVector = CP_Vector_MatrixMultiply(camMatrix, _obstacle->pos);

	if (_obstacle->sniper == 1) CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	else CP_Settings_Fill(ENEMY_COLOR());

	CP_Graphics_DrawRect(targetVector.x, targetVector.y, _obstacle->width * cam->camZoom, _obstacle->height * cam->camZoom);
}

void RenderLaser(Laser* laser)
{
	CamInfo* cam = GetCamera();
	CP_Matrix camS = CP_Matrix_Scale(CP_Vector_Set(cam->camZoom, cam->camZoom));
	CP_Matrix camT = CP_Matrix_Translate(cam->camPos);
	CP_Matrix camMatrix = CP_Matrix_Multiply(camT, camS);
	CP_Vector targetVector = CP_Vector_MatrixMultiply(camMatrix, laser->pos);

	float _laserWidth = laser->laserWidth * cam->camZoom;
	float _laserHeight = laser->laserHeight * cam->camZoom;

	switch (laser->state)
	{
	case WARNING:
		switch (laser->laserDirection)
		{
		case LD_UP:
			CP_Settings_Fill(CP_Color_Create(150, 1, 147, laser->laserAlpha));
			CP_Graphics_DrawRect(targetVector.x, targetVector.y, laser->laserWarningAttackRange * cam->camZoom, _laserHeight);
			break;
		case LD_DOWN:
			CP_Settings_Fill(CP_Color_Create(150, 1, 147, laser->laserAlpha));
			CP_Graphics_DrawRect(targetVector.x, targetVector.y, laser->laserWarningAttackRange * cam->camZoom, _laserHeight);
			break;
		case LD_LEFT:
			CP_Settings_Fill(CP_Color_Create(150, 1, 147, laser->laserAlpha));
			CP_Graphics_DrawRect(targetVector.x, targetVector.y, _laserWidth, laser->laserWarningAttackRange * cam->camZoom);
			break;
		case LD_RIGHT:
			CP_Settings_Fill(CP_Color_Create(150, 1, 147, laser->laserAlpha));
			CP_Graphics_DrawRect(targetVector.x, targetVector.y, _laserWidth, laser->laserWarningAttackRange * cam->camZoom);
			break;
		}
		break; // <- 이자식이 없어서 레이저가 이상했다
	case ATTACK:

		if (laser->sniper == 1) CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255)); // 플레이를 맞춘 탄환이면.
		else CP_Settings_Fill(ENEMY_COLOR());

		CP_Graphics_DrawRect(targetVector.x, targetVector.y, _laserWidth, _laserHeight);
		break;
	}
}

void RenderEliteShadow(Boss* _boss)
{
	if (stageState >= StageFive)
	{
		CamInfo* cam = GetCamera();
		CP_Matrix camS = CP_Matrix_Scale(CP_Vector_Set(cam->camZoom, cam->camZoom));
		CP_Matrix camT = CP_Matrix_Translate(cam->camPos);
		CP_Matrix camMatrix = CP_Matrix_Multiply(camT, camS);

		int count = enemyShadowIndex > 10 ? 10 : enemyShadowIndex;  // 최대 잔상 수 제한

		for (int i = 0; i < count; ++i)
		{
			int idx = (enemyShadowIndex - i - 1 + 100) % 100;  // 최근 위치부터 역순으로 가져오기

			CP_Vector target = CP_Vector_MatrixMultiply(camMatrix, enemyShadow[idx]);
			float alpha = 150.f - (i * 20);  // 뒤로 갈수록 투명해짐

			if (alpha < 0) alpha = 0;

			switch (invincibleColorIndex % 6)
			{
			case 0:
				CP_Settings_Fill(CP_Color_Create(200, 1, 147, (int)alpha));
				break;
			case 1:
				CP_Settings_Fill(CP_Color_Create(200, 1, 147, (int)alpha));
				break;
			case 2:
				CP_Settings_Fill(CP_Color_Create(200, 1, 147, (int)alpha));
				break;
			case 3:
				CP_Settings_Fill(CP_Color_Create(200, 1, 147, (int)alpha));
				break;
			case 4:
				CP_Settings_Fill(CP_Color_Create(200, 1, 147, (int)alpha));
				break;
			case 5:
				CP_Settings_Fill(CP_Color_Create(200, 1, 147, (int)alpha));
				break;
			case 6:
				CP_Settings_Fill(CP_Color_Create(200, 1, 147, (int)alpha));
				break;
			case 7:
				CP_Settings_Fill(CP_Color_Create(200, 1, 147, (int)alpha));
				break;
			case 8:
				CP_Settings_Fill(CP_Color_Create(200, 1, 147, (int)alpha));
				break;
			case 9:
				CP_Settings_Fill(CP_Color_Create(200, 1, 147, (int)alpha));
				break;
			case 10:
				CP_Settings_Fill(CP_Color_Create(200, 1, 147, (int)alpha));
				break;
			}

			CP_Graphics_DrawRect(target.x, target.y, cam->camZoom * _boss->size, cam->camZoom * _boss->size);
		}
	}
}

void RenderEnemyShadow()
{
	RenderEliteShadow(&elite_StageFive);
}

void RenderEnemy_StageOne()
{
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		RenderEnemy(&enemies[StageOne][i]);
	}
}

void RenderBullet_StageOne()
{
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		for (int j = 0; j < MAX_BULLETS_PER_ENEMY; j++)
		{
			RenderBullet(&Bullets_StageOne[i][j]);
		}
	}
}

void RenderEnemy_StageTwo()
{
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		RenderEnemy(&enemies[StageTwo][i]);
	}
}

void RenderLaser_StageTwo()
{
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		RenderLaser(&Lasers_StageTwo[i]);
	}
}

void RenderEnemy_StageThree()
{
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		RenderEnemy(&enemies[StageThree][i]);
	}
}

void RenderBullet_StageThree()
{
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		for (int j = 0; j < CLIP; j++)
		{
			for (int k = 0; k < MAX_BULLETS_PER_ENEMY; k++)
			{
				if (CircleBullets_StageThree[i][j][k].active)
				{
					RenderBullet(&CircleBullets_StageThree[i][j][k]);
				}
			}
		}
	}
}

void RenderEnemy_StageFour()
{
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		RenderEnemy(&enemies[StageFour][i]);
	}
}

void RenderEnemy_StageFive()
{
	RenderBoss(&elite_StageFive);
}

void RenderEnemy_StageSix()
{
	RenderEnemy(&enemy_StageSix);
}

void RenderBullet_StageSix()
{
	for (int i = 0; i < MAX_BULLETS_PER_ENEMY; i++)
	{
		RenderBullet(&Bullets_StageSix[i]);
	}
}


void RenderBoss(Boss* _boss)
{
	CamInfo* cam = GetCamera();
	CP_Matrix camS = CP_Matrix_Scale(CP_Vector_Set(cam->camZoom, cam->camZoom));
	CP_Matrix camT = CP_Matrix_Translate(cam->camPos);
	CP_Matrix camMatrix = CP_Matrix_Multiply(camT, camS);
	CP_Vector targetVector = CP_Vector_MatrixMultiply(camMatrix, _boss->pos);

	float _bossSize = _boss->size * cam->camZoom;
	if (_boss->sniper == 1) CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	else CP_Settings_Fill(ENEMY_COLOR());

	CP_Graphics_DrawRect(targetVector.x, targetVector.y, _bossSize, _bossSize);
}

void RenderBullet_BossStage()
{
	if (boss.phase < 2)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < MAX_BULLETS_PER_ENEMY; j++)
			{
				RenderBullet(&CrossBullets_Boss[i][j]);
			}
		}
	}
}

void RenderLaser_BossStage()
{
	for (int i = 0; i < MAX_LASERS; i++)
	{
		RenderLaser(&Lasers_BossStage[i]);
	}
}

void RenderBossStage()
{
	RenderBoss(&boss);
}

void RenderEnemyAll()
{
	if (stageState < StageBoss)
	{
		RenderEnemyShadow();
		RenderEnemy_StageSix();
		RenderEnemy_StageFive();
		RenderEnemy_StageFour();
		RenderEnemy_StageThree();
		RenderEnemy_StageTwo();
		RenderEnemy_StageOne();
	}
	else
	{
		RenderBossStage();
	}
}

void RenderAttackAll()
{
	if (stageState < StageBoss)
	{
		RenderBullet_StageSix();
		RenderBullet_StageThree();
		RenderLaser_StageTwo();
		RenderBullet_StageOne();
	}
	else
	{
		RenderBullet_BossStage();
		RenderLaser_BossStage();
	}
}

void RenderAll()
{
	DefaultTimerUI();

	// 적 렌더링
	RenderEnemyAll();
	RenderAttackAll();

	// 보스 렌더링

	RenderWall(wall);

	// 플레이어 관련 렌더링
	RenderPlayerShadow();
	RenderPlayer();

	// 장애물 렌더링
	//RenderObstacle(&obstacles[0][0]);

	// 디버그 UI
	//DebugUpdate();
	// 타이머 UI
}