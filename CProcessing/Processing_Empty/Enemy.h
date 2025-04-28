#pragma once
#include "cprocessing.h"
#include "Defines.h"

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
	EnemyDestination enemyDestination;
	UnitType unitType;
	int sniper;

} Enemy;

typedef struct Boss
{
	CP_Vector pos;
	float fireTime;// 쿨타임
	float fireDelay;// 쿨타임 cap
	float size;
	int active;
	int sniper;
	UnitType unitType;
} Boss;

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
	int sniper;
} Bullet;

typedef enum LaserState
{
	IDLE,	// 아무것도 안하는 상태
	WARNING, // 경고사격
	WAIT,	// 경고사격 후 + 진짜 사격전 딜레이
	ATTACK,	// 진짜 사격
}LaserState;

typedef struct Laser
{
	CP_Vector pos;
	int laserAlpha;
	int laserAlphaMax;
	
	float time;

	float idleDuration;
	float warningAttackDuration; // 경고사격 지속시간
	float waitDuration; // 경고사격 후 딜레이 (진짜 사격전 딜레이)
	float attackDuration;


	float laserWarningAttackRange;
	float laserWarningAttackRangeMax;

	float laserWidth;
	float laserHeight;
	LaserDirection laserDirection;
	LaserState state;
	int sniper;
} Laser;

Boss boss;
Enemy enemies[3][MAX_ENEMIES];
Bullet CircleBullets_StageThree[MAX_ENEMIES][MAGAZINE][MAX_BULLETS_PER_ENEMY];
Bullet Bullets_StageOne[MAX_ENEMIES][MAX_BULLETS_PER_ENEMY];
Laser Lasers_StageTwo[MAX_ENEMIES];

void EnemyInit_BossStage(Boss*);
void EnemyInit_StageOne(Enemy*);
void EnemyMove_StageOne(Enemy*);
void EnemyInit_StageTwo(Enemy*, Laser*);
void EnemyInit_StageThree(Enemy*);
void LaserInit_StageTwo(Laser*);

void BulletConditioner(Enemy*, Bullet*);
void CircleBulletConditioner(Enemy*, Bullet[MAGAZINE][MAX_BULLETS_PER_ENEMY]);
void CircleBulletFire(Enemy*, Bullet*);
void DirectBulletFire(Enemy*, Bullet*);

void CreateLaser(Enemy*, Laser*);
void LaserAttack(Laser*);

void AppearBoss(Boss*);
void DisableEnemy(Enemy*);
void DisappearBoss(Boss*);