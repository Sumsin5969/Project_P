#include "cprocessing.h"
#include "PP_Renderer.h"
#include "ZoomCamera.h"
#include "../Defines.h"
#include "stdio.h"
#include "GameManager.h"
#include <math.h>
#include "Collision.h"

void RenderWall(Obstacle* _obstacles)
{

	CP_Settings_Fill(CP_Color_Create(200, 1, 147, 255));
	CP_Settings_NoStroke();

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
	CP_Graphics_DrawCircle(targetVector.x, targetVector.y, _bulletSize);
}

void RenderObstacle(Obstacle* _obstacle)
{
	CamInfo* cam = GetCamera();
	CP_Matrix camS = CP_Matrix_Scale(CP_Vector_Set(cam->camZoom, cam->camZoom));
	CP_Matrix camT = CP_Matrix_Translate(cam->camPos);
	CP_Matrix camMatrix = CP_Matrix_Multiply(camT, camS);
	CP_Vector targetVector = CP_Vector_MatrixMultiply(camMatrix, _obstacle->pos);

	CP_Settings_Fill(CP_Color_Create(20, 10, 147, 150));

	CP_Graphics_DrawRect(targetVector.x, targetVector.y, _obstacle->width * cam->camZoom, _obstacle->height * cam->camZoom);
}

void RenderLaser(Enemy* enemy, Laser* laser)
{
	CamInfo* cam = GetCamera();
	CP_Matrix camS = CP_Matrix_Scale(CP_Vector_Set(cam->camZoom, cam->camZoom));
	CP_Matrix camT = CP_Matrix_Translate(cam->camPos);
	CP_Matrix camMatrix = CP_Matrix_Multiply(camT, camS);
	CP_Vector targetVector = CP_Vector_MatrixMultiply(camMatrix, laser->pos);
	float LaserWidth = enemy[0].size * cam->camZoom;
	CP_Settings_Fill(CP_Color_Create(20, 10, 147, 150));

	CP_Graphics_DrawRect(targetVector.x, targetVector.y, cam->camZoom, LaserWidth*cam->camZoom);
}

void RenderBoss()

{

}

void RenderAll()
{

}




