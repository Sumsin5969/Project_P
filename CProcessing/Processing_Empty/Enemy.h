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
	EnemyDestination enemyDestination;
	FireType fireType;
	int sniper;

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
	int sniper;
} Bullet;

typedef struct Timer
{
	float time;
	float timeMax;
} Timer;

int LaserIsTimeout(Timer);

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


Enemy enemies[StageLastIndex][MAX_ENEMIES];
Bullet CircleBullets_StageThree[MAX_ENEMIES][MAGAZINE][MAX_BULLETS_PER_ENEMY];
Bullet Bullets_StageOne[MAX_ENEMIES][MAX_BULLETS_PER_ENEMY];
Laser Lasers_StageTwo[MAX_ENEMIES];
//void BulletInit(Bullet* bullets);
void EnemyInit_StageOne(Enemy*);
void EnemyInit_StageTwo(Enemy*, Laser*);
void EnemyInit_StageThree(Enemy*);
void LaserInit_StageTwo(Laser*);
void EnemyMove_StageOne(Enemy*);
void BulletConditioner(Enemy*, Bullet*);
void CircleBulletConditioner(Enemy*, Bullet*, float);
void CircleBulletFire(Enemy*, Bullet*);
void DirectBulletFire(Enemy*, Bullet*);
void LaserAttack(Laser*);
void DisableEnemy(Enemy*);
void CreateLaser(Enemy*, Laser*);