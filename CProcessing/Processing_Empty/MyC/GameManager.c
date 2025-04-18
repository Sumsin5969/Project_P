#include "stdio.h"
#include "stdlib.h"
#include "ZoomCamera.h"
#include "PP_Renderer.h"
#include "../Defines.h"
#include "JhDebug.h"
#include "Collision.h"
#include "../Enemy.h"
#include "../Obstacle.h"

Obstacle wall[MAX];
//Obstacle* obstacle;
//BossCharacter* boss;

PlayerState playerState;



void InitGameManager()
{
	InitCamera();

	PlayerInit();

	BulletInit();

	EnemyInit();

	InitDebuging();

	InitWall(&wall[0]);
	InitWall(&wall[1]);
	InitWall(&wall[2]);
	InitWall(&wall[3]);

}

void GMUpdate()
{
	PlayerMove();
	Dash();
	CheckWall(&wall[0]);
	CheckWall(&wall[1]);
	CheckWall(&wall[2]);
	CheckWall(&wall[3]);

}

void GMLateUpdate()
{
	CP_Graphics_ClearBackground(CP_Color_Create(15, 15, 15, 0));

	EnemyLaserAttack();

	EnemyBulletFire();

	RenderWall(wall);

	RenderEnemy();

	RenderPlayer();


	DebugUpdate();
}
// 바로 아래 FreeAll 작성 시 찾기 편하도록 동적할당 할 때마다 그 목록을 여기에 적겠음.
// cam, EnemyInit, 
void FreeAll()
{ 
	DestroyPlayer();
	DestroyEnemy();
	DestroyCam();
}
