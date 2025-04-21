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
	int active;
} Enemy;

typedef struct Bullet
{
	CP_Vector projPos;// 투사체 좌표
	float projSpd;// 투사체 속도
	float projTime;// 투사체 지속시간
	float fireTime;// 쿨타임
	float fireDelay;// 쿨타임 cap
	float fireAngle;
	float degree;
	float size;
	CP_Vector fireDir;
	int active;
} Bullet;
Enemy enemies[MAX_ENEMIES];
Bullet allBullets[MAX_ENEMIES][MAX_BULLETS_PER_ENEMY];
//void BulletInit(Bullet* bullets);
void EnemyInit();
void DisableEnemy();