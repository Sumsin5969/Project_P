#include "cprocessing.h"
#include "PP_Renderer.h"
#include "ZoomCamera.h"
#include "../Defines.h"
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

//void RenderObstacle(Obstacle _obstacles[][2])
//{
//	for (int i = 0; i < 7; ++i)
//	{
//		for (int j = 0; j < 2; ++j)
//		{
//			float x = _obstacles[i][j].pos.x;
//			float y = _obstacles[i][j].pos.y;
//			float w = _obstacles[i][j].width;
//			float h = _obstacles[i][j].height;
//			CP_Graphics_DrawRect(x, y, w, h);
//		}
//	}
//}

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


void RenderEnemy(Enemy* _enemy)
{
	CamInfo* cam = GetCamera();
	CP_Matrix camS = CP_Matrix_Scale(CP_Vector_Set(cam->camZoom, cam->camZoom));
	CP_Matrix camT = CP_Matrix_Translate(cam->camPos);
	CP_Matrix camMatrix = CP_Matrix_Multiply(camS, camT);
	CP_Vector targetVector = CP_Vector_MatrixMultiply(camMatrix, _enemy->pos);

	float _enemySize = _enemy->size * cam->camZoom;

	CP_Graphics_DrawRect(targetVector.x, targetVector.y, _enemySize, _enemySize);
}

//void RenderEnemy_Sumsin()
//{
//	CamInfo* cam = GetCamera();
//	CP_Matrix pcS;
//	pcS = CP_Matrix_Scale(CP_Vector_Set(cam->camZoom, cam->camZoom));
//	CP_Matrix pcT;
//	pcT = CP_Matrix_Translate(cam->camPos);
//
//	CP_Matrix camMatrix = CP_Matrix_Multiply(pcT, pcS);
//
//	CP_Settings_Fill(CP_Color_Create(238, 1, 147, 255));
//	for (int i = 0; i < MAX_ENEMIES; i++)
//	{
//		CP_Vector targetVector = CP_Vector_MatrixMultiply(camMatrix, enemies[i].pos);
//		CP_Graphics_DrawRect(targetVector.x, targetVector.y, cam->camZoom * enemies[i].size, cam->camZoom * enemies[i].size);
//	}
//}

void RenderBullet(Bullet* _bullet)
{

	CamInfo* cam = GetCamera();
	CP_Matrix camS = CP_Matrix_Scale(CP_Vector_Set(cam->camZoom, cam->camZoom));
	CP_Matrix camT = CP_Matrix_Translate(cam->camPos);
	CP_Matrix camMatrix = CP_Matrix_Multiply(camS, camT);
	CP_Vector targetVector = CP_Vector_MatrixMultiply(camMatrix, _bullet->projPos);

	float _bulletSize = _bullet->size * cam->camZoom;

	CP_Graphics_DrawRect(targetVector.x, targetVector.y, _bulletSize, _bulletSize);
}

void RenderObstacle(Obstacle* _obstacle)
{
	CamInfo* cam = GetCamera();
	CP_Matrix camS = CP_Matrix_Scale(CP_Vector_Set(cam->camZoom, cam->camZoom));
	CP_Matrix camT = CP_Matrix_Translate(cam->camPos);
	CP_Matrix camMatrix = CP_Matrix_Multiply(camS, camT);
	CP_Vector targetVector = CP_Vector_MatrixMultiply(camMatrix, _obstacle->pos);

	CP_Graphics_DrawRect(targetVector.x, targetVector.y, _obstacle->width * cam->camZoom, _obstacle->height * cam->camZoom);
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
// 원형 발사 패턴
// 탄환의 position을 업데이트 해주고 Draw도 해줌
// 탄환의 개수는 MAX_BULLETS_PER_ENEMY 만큼 있어야 함 
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
		else
		{
			b[i].projPos.x += b[i].projSpd * b[i].fireDir.x * dt;
			b[i].projPos.y += b[i].projSpd * b[i].fireDir.y * dt;
			b[i].degree += 360.f / MAX_BULLETS_PER_ENEMY;
			CP_Settings_Fill(CP_Color_Create(238, 1, 147, 255));
			CP_Vector targetVector = CP_Vector_MatrixMultiply(camMatrix, b[i].projPos);
			CP_Graphics_DrawCircle(targetVector.x, targetVector.y, b[i].size * cam->camZoom);
		}
		if (b[i].projTime > b[i].fireDelay)
		{
			b[i].projTime = 0;
			b[i].projPos.x = originX;
			b[i].projPos.y = originY;
		}
	}
}

// 약간 유도 되는 탄 발사
// 탄환의 position 업데이트 및 탄환 Draw
// 
void ChasingBulletFire(Enemy* e, Bullet* b)
{
	CamInfo* cam = GetCamera();
	CP_Matrix pcS;
	pcS = CP_Matrix_Scale(CP_Vector_Set(cam->camZoom, cam->camZoom));
	CP_Matrix pcT;
	pcT = CP_Matrix_Translate(cam->camPos);
	CP_Matrix camMatrix = CP_Matrix_Multiply(pcT, pcS);
	float dt = CP_System_GetDt();
	float originX = e->pos.x;
	float originY = e->pos.y;
	b->projTime += dt;
	if (!b->active)
	{
		b->projPos.x = originX;
		b->projPos.y = originY;
		b->active = 1;
	}
	else
	{
		CP_Vector direction = CP_Vector_Subtract(player->pos, e->pos);
		b->fireDir = CP_Vector_Normalize(direction);
		b->projPos.x += b->projSpd * b->fireDir.x * dt;
		b->projPos.y += b->projSpd * b->fireDir.y * dt;
		CP_Settings_Fill(CP_Color_Create(238, 1, 147, 255));
		CP_Vector targetVector = CP_Vector_MatrixMultiply(camMatrix, b->projPos);
		CP_Graphics_DrawCircle(targetVector.x, targetVector.y, b->size * cam->camZoom);
	}
	if (b->projTime > b->fireDelay)
	{
		b->projTime = 0;
		b->projPos.x = originX;
		b->projPos.y = originY;
	}
}
// 발사 시점 플레이어 위치로 직진하는 탄환 발사
// 탄환의 position 업데이트 및 탄환 Draw
// e: 탄환의 origin position, 발사 방향을 구하기 위한 Enemy 정보
// b: Enemy.c에서 초기화한 탄환 배열: 탄환의 position 업데이트, position 기반 렌더링에 사용할
//탄환 정보
void DirectBulletFire(Enemy* e, Bullet* b)
{
	CamInfo* cam = GetCamera();
	CP_Matrix pcS;
	pcS = CP_Matrix_Scale(CP_Vector_Set(cam->camZoom, cam->camZoom));
	CP_Matrix pcT;
	pcT = CP_Matrix_Translate(cam->camPos);
	CP_Matrix camMatrix = CP_Matrix_Multiply(pcT, pcS);
	float dt = CP_System_GetDt();
	float originX = e->pos.x;
	float originY = e->pos.y;
	b->projTime += dt;
	if (!b->active)
	{
		b->projPos.x = originX;
		b->projPos.y = originY;
		CP_Vector direction = CP_Vector_Subtract(player->pos, e->pos);
		b->fireDir = CP_Vector_Normalize(direction);
		b->active = 1;
	}
	else
	{
		b->projPos.x += b->projSpd * b->fireDir.x * dt;
		b->projPos.y += b->projSpd * b->fireDir.y * dt;
		CP_Settings_Fill(CP_Color_Create(238, 1, 147, 255));
		CP_Vector targetVector = CP_Vector_MatrixMultiply(camMatrix, b->projPos);
		CP_Graphics_DrawCircle(targetVector.x, targetVector.y, b->size * cam->camZoom);
	}
	if (b->projTime > b->fireDelay)
	{
		b->projTime = 0;
		b->projPos.x = originX;
		b->projPos.y = originY;
		CP_Vector direction = CP_Vector_Subtract(player->pos, e->pos);
		b->fireDir = CP_Vector_Normalize(direction);
	}
}



void RenderBoss()

{

}

void RenderAll()
{

}




