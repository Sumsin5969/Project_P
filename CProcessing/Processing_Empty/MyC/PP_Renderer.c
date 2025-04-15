#include "cprocessing.h"
#include "../unit.h"
#include "ZoomCamera.h"
#include "../Defines.h"

#define WIDTH 1760
#define HEIGHT 990
#define WALLWIDTHSIZE 30
#define WALLHEIGHTSIZE 24

void RenderWall()
{

}

void RenderPlayer(PlayerCharacter* _playerCharacter)
{
	CamInfo* cam = GetCamera();

	
	//CP_Vector baseV = CP_Vector_Set(WIDTH / 2 - _playerCharacter->pos.x, HEIGHT / 2 - _playerCharacter->pos.y);

	CP_Matrix pcS;
	pcS = CP_Matrix_Scale(CP_Vector_Set(cam->camZoom, cam->camZoom));
	CP_Matrix pcT;
	pcT = CP_Matrix_Translate(cam->camPos);

	CP_Matrix camMatrix = CP_Matrix_Multiply(pcT,pcS);

	CP_Vector targetVector = CP_Vector_MatrixMultiply(camMatrix, _playerCharacter->pos);

	CP_Settings_Fill(CP_Color_Create(36, 235, 238, 255));

	CP_Graphics_DrawCircle(targetVector.x, targetVector.y, cam->camZoom * _playerCharacter->size);
}

void RenderEnemy(Enemy* _enemy)
{
	CP_Settings_Fill(CP_Color_Create(50, 50, 50, 255));
	CP_Graphics_DrawRect(_enemy->pos.x, _enemy->pos.y, _enemy->size, _enemy->size);
}

void RenderObstacle(Obstacle* _obstacle)
{
	CP_Settings_Fill(CP_Color_Create(255, 255, 0, 255));
	CP_Graphics_DrawRect(_obstacle->pos.x, _obstacle->pos.y, _obstacle->width, _obstacle->height);
}

void RenderBoss()

{

}

void RenderAll()
{

}


