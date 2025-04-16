#include "cprocessing.h"
#include "PP_Renderer.h"
#include "ZoomCamera.h"
#include "../Defines.h"
#include "../Player.h"
#include "../Enemy.h"
#include "../Obstacle.h"

#include "stdio.h"

void RenderWall(Obstacle* _obstacles)
{
	CP_Settings_Fill(CP_Color_Create(200, 1, 147, 255));
	CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 0));

	CamInfo* cam = GetCamera();

	for (int i = 0; i < MAX; ++i)
	{
		CP_Vector targetVector = CP_Vector_MatrixMultiply(cam->camMatrix, _obstacles[i].pos);

		CP_Graphics_DrawRect(targetVector.x, targetVector.y, _obstacles[i].width, _obstacles[i].height);
	}

	/*for (int i = 0; i < MAX; ++i)
	{
		CP_Graphics_DrawRect(_obstacles[i].pos.x, _obstacles[i].pos.y, _obstacles[i].width, _obstacles[i].height);
	}*/


}

void RenderPlayer(PlayerCharacter* _playerCharacter)
{
	CamInfo* cam = GetCamera();


	//CP_Vector baseV = CP_Vector_Set(WIDTH / 2 - _playerCharacter->pos.x, HEIGHT / 2 - _playerCharacter->pos.y);

	CP_Matrix pcS;
	pcS = CP_Matrix_Scale(CP_Vector_Set(cam->camZoom, cam->camZoom));
	CP_Matrix pcT;
	pcT = CP_Matrix_Translate(cam->camPos);

	CP_Matrix camMatrix = CP_Matrix_Multiply(pcT, pcS);

	CP_Vector targetVector = CP_Vector_MatrixMultiply(camMatrix, _playerCharacter->pos);

	CP_Settings_Fill(CP_Color_Create(36, 235, 238, 255));

	CP_Graphics_DrawCircle(targetVector.x, targetVector.y, cam->camZoom * _playerCharacter->size);
}

void RenderEnemy(Enemy* _enemy)
{
	CP_Settings_Fill(CP_Color_Create(50, 50, 50, 255));
	CP_Graphics_DrawRect(_enemy->pos.x, _enemy->pos.y, _enemy->size, _enemy->size);
}

//void RenderObstacle(Obstacle* _obstacle)
//{
//	CP_Settings_Fill(CP_Color_Create(255, 255, 0, 255));
//	CP_Graphics_DrawRect(_obstacle->pos.x, _obstacle->pos.y, _obstacle->width, _obstacle->height);
//}

int LaserAlpha = 50;
int LaserAlphaMax = 125;
float LaserChargeTime = 1.5f;
float LaserChargeWidth = 0.f;
float LaserWidth = 150.f;
float LaserTimer = 0.f;
float LaserAttackTimer = 0.f;
float LaserTime = 1.f;
float LaserDelay = 0.5f;
float LaserDelayTimer = 0.f;
void EnemyLaserAttack()
{
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
		CP_Graphics_DrawRect(WIDTH / 2, 100, LaserChargeWidth, HEIGHT*10); // 레이저 위치
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
			CP_Graphics_DrawRect(WIDTH / 2, 100, 100, HEIGHT*10);
		}
	}
}

void RenderBoss()

{

}

void RenderAll()
{

}


