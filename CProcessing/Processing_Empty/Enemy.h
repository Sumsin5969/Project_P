#pragma once
#include "cprocessing.h"
#include "Defines.h"


// 플레이어 위치로 발사할 적
typedef struct Enemy
{
	CP_Vector pos;
	float spd;
	int isAttack;
	float fireTime;// 쿨타임
	float fireDelay;// 쿨타임 cap
	float size;
	int magazine;
	int active;
	EnemyPosition enemyPosition;
	FireType fireType;
} Enemy;

typedef struct Bullet
{
	CP_Vector projPos;// 투사체 좌표
	float projSpd;// 투사체 속도
	float projTime;// 투사체 지속시간
	float degree;
	float fireAngle; // 여기부터 렌더러에서 조절
	CP_Vector fireDir;
	int active;
	float size;
	CP_Vector direction;
} Bullet;

typedef struct Laser
{
	int a;
} Laser;


Enemy enemies[StageLastIndex][MAX_ENEMIES];
Bullet CircleBullets[MAX_ENEMIES][MAX_BULLETS_PER_ENEMY];
Bullet PDBullets[MAX_ENEMIES][MAX_BULLETS_PER_ENEMY];
//void BulletInit(Bullet* bullets);
void EnemyInit_StageOne(Enemy*);
void EnemyMove_StageOne(Enemy*);
void EnemyInit_StageTwo(Enemy*);
void DisableEnemy(Enemy*);
void BulletConditioner(Enemy*, Bullet*);
void CircleBulletFire(Enemy*, Bullet*);
void DirectBulletFire(Enemy*, Bullet*);
void LaserAttack();