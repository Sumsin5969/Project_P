#pragma once
#include "cprocessing.h"

typedef struct Enemy
{
	CP_Vector pos;
	float spd;
	int isAttack;
	float appTime;
	float size;
} Enemy;

typedef struct Obstacle
{
	CP_Vector pos;
	float width;
	float height;
} Obstacle;

typedef struct BossCharacter
{
	CP_Vector pos;
	float size;
	// 보스에 추가될 요소들


} BossCharacter;
