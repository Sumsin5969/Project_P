#include "cprocessing.h"
#include "PP_Renderer.h"
#include "ZoomCamera.h"
#include "../Defines.h"
#include "../Player.h"
#include "../Enemy.h"
#include "../Obstacle.h"
#include "stdio.h"
#include <math.h>

void RenderWall(Obstacle* _obstacles)
{
	CP_Settings_Fill(CP_Color_Create(200, 1, 147, 255));
	CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 0));

	CamInfo* cam = GetCamera();

	for (int i = 0; i < MAX; ++i)
	{
		CP_Graphics_DrawRect(_obstacles[i].pos.x, _obstacles[i].pos.y, _obstacles[i].width, _obstacles[i].height);
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

	CP_Vector targetVector = CP_Vector_MatrixMultiply(camMatrix, enemy->pos);

	CP_Settings_Fill(CP_Color_Create(100, 100, 100, 255));

	CP_Graphics_DrawRect(targetVector.x, targetVector.y, cam->camZoom * enemy->size, cam->camZoom * enemy->size);
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
	CP_Matrix camMatrix = CP_Matrix_Multiply(pcT, pcS);
	CP_Vector targetVector = CP_Vector_MatrixMultiply(camMatrix, enemy->pos);

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
		CP_Graphics_DrawRect(WIDTH / 2, 100, LaserChargeWidth * cam->camZoom, HEIGHT*10 * cam->camZoom); // 레이저 위치
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
			CP_Graphics_DrawRect(WIDTH / 2, 100, 100 * cam->camZoom, HEIGHT*10 * cam->camZoom);
		}
	}
}


void EnemyBulletFire()
{
	float dt = CP_System_GetDt();
	float originX = enemy->pos.x;
	float originY = enemy->pos.y;
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (!bullets[i].active)
		{
			bullets[i].projPos.x = originX;
			bullets[i].projPos.y = originY;
			bullets[i].fireAngle = CP_Math_Radians(bullets[i].degree);
			bullets[i].fireDir.x = cosf(bullets[i].fireAngle);
			bullets[i].fireDir.y = sinf(bullets[i].fireAngle);
			bullets[i].active = 1;
			bullets[i].fireTime = 0;
		}
		if (bullets[i].active)
		{
			bullets[i].fireTime += dt;
			if (bullets[i].fireTime > bullets[i].fireCoolTime)
			{
				bullets[i].projPos.x += bullets[i].projSpd * bullets[i].fireDir.x * dt;
				bullets[i].projPos.y += bullets[i].projSpd * bullets[i].fireDir.y * dt;
				bullets[i].degree += 360.f / MAX_BULLET;
				CP_Settings_Fill(CP_Color_Create(238, 1, 147, 255));
				CP_Graphics_DrawCircle(bullets[i].projPos.x, bullets[i].projPos.y, bullets[i].size);
			}
		}
	}
}

void RenderBoss()

{

}

void RenderAll()
{

}


