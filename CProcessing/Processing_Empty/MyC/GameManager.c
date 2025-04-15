#include "stdio.h"
#include "stdlib.h"
#include "../unit.h"
#include "ZoomCamera.h"
#include "PP_Renderer.h"
#include "../Defines.h"
#include "JhDebug.h"



typedef struct Units
{
	PlayerCharacter* playerCharacter;
	Enemy* enemyCharacter;
	Obstacle* obstacle;
	BossCharacter* boss;
} Units;

Units* allUnit;

void InitGameManager()
{
	allUnit = (Units*)calloc(1, sizeof(Units));
	if (allUnit == NULL)
	{
		printf("메모리 할당실패");
		exit(1); // todo: CProcessing에서 제공하는 종료 함수 사용해용
	}

	PlayerInit();

	allUnit->playerCharacter = GetPlayer();

	InitCamera();

	InitDebuging();
}

void GMUpdate()
{
	PlayerMove();
	Dash();
}

void GMLateUpdate()
{
	CP_Graphics_ClearBackground(CP_Color_Create(15, 15, 15, 0));

	RenderWall();

	RenderPlayer(allUnit->playerCharacter);

	DebugUpdate();
}

void FreeAll()
{
	
}
