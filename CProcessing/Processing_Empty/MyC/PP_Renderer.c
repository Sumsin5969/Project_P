#include "cprocessing.h"
#include "PP_Renderer.h"
#include "ZoomCamera.h"
#include "../Defines.h"
#include "stdio.h"
#include "GameManager.h"
#include <math.h>
#include "Collision.h"

int invincibleColorIndex = 0;


void RenderWall(Obstacle* _obstacles)
{
	CP_Settings_Fill(CP_Color_Create(200, 1, 147, 255));
	CP_Settings_NoStroke();

	for (int i = 0; i < MAX; ++i)
	{
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

}


void RenderEnemy(Enemy* _enemy)
{
	CamInfo* cam = GetCamera();
	CP_Matrix camS = CP_Matrix_Scale(CP_Vector_Set(cam->camZoom, cam->camZoom));
	CP_Matrix camT = CP_Matrix_Translate(cam->camPos);
	CP_Matrix camMatrix = CP_Matrix_Multiply(camT, camS);
	CP_Vector targetVector = CP_Vector_MatrixMultiply(camMatrix, _enemy->pos);

	float _enemySize = _enemy->size * cam->camZoom;

	CP_Settings_Fill(CP_Color_Create(200, 1, 147, 255));
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
	CP_Settings_Fill(CP_Color_Create(200, 1, 147, 255));
	CP_Graphics_DrawCircle(targetVector.x, targetVector.y, _bulletSize);
}

void RenderObstacle(Obstacle* _obstacle)
{
	CamInfo* cam = GetCamera();
	CP_Matrix camS = CP_Matrix_Scale(CP_Vector_Set(cam->camZoom, cam->camZoom));
	CP_Matrix camT = CP_Matrix_Translate(cam->camPos);
	CP_Matrix camMatrix = CP_Matrix_Multiply(camT, camS);
	CP_Vector targetVector = CP_Vector_MatrixMultiply(camMatrix, _obstacle->pos);

	CP_Settings_Fill(ENEMY_COLOR());

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
		CP_Settings_Fill(CP_Color_Create(200, 1, 147, laser->laserAlpha));
		CP_Graphics_DrawRect(targetVector.x, targetVector.y, _laserWidth / (cam->camZoom * (float)2), laser->laserWarningAttackRange * cam->camZoom);
		break;
	case ATTACK:
		CP_Settings_Fill(CP_Color_Create(200, 1, 147, 255));
		CP_Graphics_DrawRect(targetVector.x, targetVector.y, _laserWidth * (cam->camZoom), _laserHeight * cam->camZoom);
		break;
	}
}

void RenderBoss()
{

}

void RenderAll()
{

}




