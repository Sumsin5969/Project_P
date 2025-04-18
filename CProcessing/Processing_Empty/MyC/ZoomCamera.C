#include "stdlib.h"
#include "stdio.h"
#include "ZoomCamera.h"
#include "cprocessing.h"
#include "math.h"
#include "GameManager.h"
#include "../Defines.h"
CamInfo* cam;

void InitCamera()
{
	cam = (CamInfo*)calloc(1, sizeof(CamInfo));

	if (cam == NULL)
	{
		printf("[ERROR] Failed to allocate memory for camera!\n");
		return;
	}

	cam->camPos = CP_Vector_Set(WIDTH * 0.5f, HEIGHT * 0.5f); // 카메라 포지션을 중앙으로

	cam->camZoom = 1;

	// Create a transform matrix
	CP_Matrix scale = CP_Matrix_Scale(CP_Vector_Set(cam->camZoom, cam->camZoom)); // 스케일 설정

	// 이렇게 되면 카메라가 반대방향으로 이동할 수 있다? // ppt 참고해야할것?
	CP_Matrix translate = CP_Matrix_Translate(cam->camPos);	// 이동 

	CP_Matrix transform = CP_Matrix_Multiply(translate, scale); // transform = T x S


	cam->camMatrix = transform;
}

CamInfo* GetCamera()
{
	if (cam == NULL)
	{
		printf("Error: Camera not initialized!\n");
		return NULL;
	}
	CP_Matrix scale = CP_Matrix_Scale(CP_Vector_Set(cam->camZoom,cam->camZoom));
	//CP_Matrix rotate = CP_Matrix_Rotate(cam.rota);
	CP_Matrix translate = CP_Matrix_Translate(CP_Vector_Set(-cam->camPos.x, -cam->camPos.y));

	cam->camMatrix = CP_Matrix_Multiply(scale, translate);

	return cam;
}

void ZoomIn()
{
	cam->camZoom *= 1.25f;
	// 소수점 둘째자리까지 반올림
	//cam->camZoom = (float)round((cam->camZoom * 100) / 100);
}
void ZoomOut()
{
	cam->camZoom /= 1.25f;
	//cam->camZoom = (float)round((cam->camZoom * 100) / 100);
}

void DestroyCam() //todo 게임매니저 혹은 메인에 넣을것
{
	free(cam);
	cam = NULL;
}

