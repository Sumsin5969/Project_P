#include "cprocessing.h"
#include "PP_Renderer.h"
#include "ZoomCamera.h"
#include "../Defines.h"
#include "../Player.h"
#include "../Enemy.h"
#include "../Obstacle.h"
#include "stdio.h"
#include "GameManager.h"
#include <math.h>

void RenderWall(Obstacle* _obstacles)
{
	CP_Settings_Fill(CP_Color_Create(200, 1, 147, 255));
	CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 0));

	for (int i = 0; i < MAX; ++i)
	{
		CP_Graphics_DrawRect(_obstacles[i].pos.x, _obstacles[i].pos.y, _obstacles[i].width, _obstacles[i].height);
	}
}

void RenderObstacle(Obstacle _obstacles[7][2])
{
	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			_obstacles[i][j];
		}
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

	CP_Settings_Fill(CP_Color_Create(36, 235, 238, 255));

	CP_Graphics_DrawCircle(targetVector.x, targetVector.y, cam->camZoom * player->size);
}

void RenderEnemy()
{
	CamInfo* cam = GetCamera();
	CP_Matrix pcS;
	pcS = CP_Matrix_Scale(CP_Vector_Set(cam->camZoom, cam->camZoom));
	CP_Matrix pcT;
	pcT = CP_Matrix_Translate(cam->camPos);

	CP_Matrix camMatrix = CP_Matrix_Multiply(pcT, pcS);

	CP_Settings_Fill(CP_Color_Create(238, 1, 147, 255));
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		CP_Vector targetVector = CP_Vector_MatrixMultiply(camMatrix, enemies[i].pos);
		CP_Graphics_DrawRect(targetVector.x, targetVector.y, cam->camZoom * enemies[i].size, cam->camZoom * enemies[i].size);
	}
}

//void RenderObstacle(Obstacle* _obstacle)
//{
//	CP_Settings_Fill(CP_Color_Create(255, 255, 0, 255));
//	CP_Graphics_DrawRect(_obstacle->pos.x, _obstacle->pos.y, _obstacle->width, _obstacle->height);
//}

int LaserAlpha = 50; // 전조 알파값
int LaserAlphaMax = 125; // 전조 최대 알파값
float LaserTimer = 0.f; // 전조 시간
float LaserChargeTime = 1.5f; // 전조 시간 cap
float LaserChargeWidth = 0.f; // 전조 범위
float LaserWidth = 150.f; // 전조 범위 cap
float LaserAttackTimer = 0.f; // 공격 시간
float LaserTime = 1.f; // 공격 시간 cap
float LaserDelay = 0.5f; // 전조 후 발사 전 사라질 시간 cap
float LaserDelayTimer = 0.f; // 사라질 시간
void LaserAttack()
{
	CamInfo* cam = GetCamera();
	CP_Matrix pcS;
	pcS = CP_Matrix_Scale(CP_Vector_Set(cam->camZoom, cam->camZoom));
	CP_Matrix pcT;
	pcT = CP_Matrix_Translate(cam->camPos);

	float dt = CP_System_GetDt();
	if (LaserTimer > LaserChargeTime && LaserAttackTimer > LaserTime)
	{
		LaserTimer = 0.f;
		LaserAttackTimer = 0.f;
		LaserChargeWidth = 0.f;
		LaserDelayTimer = 0.f;
	}
	if (LaserTimer < LaserChargeTime)
	{
		LaserTimer += dt * 1.5f;
		LaserChargeWidth += dt * 100.f;
		LaserAlpha = (int)(LaserTimer / LaserChargeTime * LaserAlphaMax);
		if (LaserAlpha > LaserAlphaMax) LaserAlpha = LaserAlphaMax;
		if (LaserChargeWidth > LaserWidth) LaserChargeWidth = LaserWidth;
		CP_Settings_Fill(CP_Color_Create(238, 1, 147, LaserAlpha));
		CP_Settings_NoStroke();
		CP_Graphics_DrawRect(WIDTH / 2, 100, LaserChargeWidth * cam->camZoom, HEIGHT * 10 * cam->camZoom); // 레이저 위치
	}
	else if (LaserDelayTimer < LaserDelay)
	{
		LaserDelayTimer += dt;
	}
	else
	{
		LaserAttackTimer += dt;
		if (LaserAttackTimer < LaserTime)
		{
			CP_Settings_Fill(CP_Color_Create(238, 1, 147, 255));
			CP_Graphics_DrawRect(WIDTH / 2, 100, 100 * cam->camZoom, HEIGHT * 10 * cam->camZoom);
		}
	}
}


void CircleBulletFire(Enemy* e, Bullet* b)
{
	CamInfo* cam = GetCamera();
	CP_Matrix pcS;
	pcS = CP_Matrix_Scale(CP_Vector_Set(cam->camZoom, cam->camZoom));
	CP_Matrix pcT;
	pcT = CP_Matrix_Translate(cam->camPos);
	CP_Matrix camMatrix = CP_Matrix_Multiply(pcT, pcS);
	float dt = CP_System_GetDt();
	for (int i = 0; i < MAX_BULLETS_PER_ENEMY; i++)
	{
		float originX = e->pos.x;
		float originY = e->pos.y;
		b[i].projTime += dt;
		if (!b[i].active)
		{
			b[i].projPos.x = originX;
			b[i].projPos.y = originY;
			b[i].fireAngle = CP_Math_Radians(b[i].degree);
			b[i].fireDir.x = cosf(b[i].fireAngle);
			b[i].fireDir.y = sinf(b[i].fireAngle);
			b[i].active = 1;
		}
		if (b[i].active)
		{
			b[i].fireTime += dt;
			if (b[i].fireTime > b[i].fireCoolTime)
			{
				b[i].projPos.x += b[i].projSpd * b[i].fireDir.x * dt;
				b[i].projPos.y += b[i].projSpd * b[i].fireDir.y * dt;
				b[i].degree += 360.f / MAX_BULLETS_PER_ENEMY;
				CP_Settings_Fill(CP_Color_Create(238, 1, 147, 255));
				CP_Vector targetVector = CP_Vector_MatrixMultiply(camMatrix, b[i].projPos);
				CP_Graphics_DrawCircle(targetVector.x, targetVector.y, b[i].size * cam->camZoom);
			}
		}
		if (b[i].projTime > 1.f)
		{
			b[i].projTime = 0;
			b[i].projPos.x = originX;
			b[i].projPos.y = originY;
		}
	}
}

void RenderBoss()

{

}

void RenderAll()
{

}




