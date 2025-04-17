#pragma once
#include "cprocessing.h"
#include "Defines.h"
typedef struct Enemy
{
	CP_Vector pos;
	float spd;
	int isAttack;
	float appTime;
	float size;
} Enemy;
Enemy* enemy;

typedef struct Bullet
{
	CP_Vector projPos;// 투사체 좌표
	float projSpd;// 투사체 속도
	float fireTime;// 투사체 지속시간
	float fireRate;// 투사체 연사 속도
	float fireAngle;
	float degree;
	CP_Vector fireDir;
	int active;
} Bullet;
Bullet bullets[MAX_BULLET];
void BulletInit();
void EnemyInit();
void DestroyEnemy();