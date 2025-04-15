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

void EnemyInit(Enemy* enemy);
void EnemyAttack();