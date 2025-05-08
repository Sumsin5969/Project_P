#pragma once
#include "cprocessing.h"
#include "Defines.h"

typedef struct Enemy
{
	CP_Vector pos;
	EnemyDestination enemyDestination; // 현재 위치
	float spd;

	float fireTime;// 쿨타임
	float fireDelay;// 쿨타임 cap
	int magazine; // 탄창

	float size;
	float oriSize;

	int active;

	UnitType unitType;
	int sniper; // 플레이어와 충돌한 적
} Enemy;

typedef struct Boss
{
	CP_Vector pos;
	EnemyDestination enemyDestination;
	float spd;
	CP_Vector dashDir;
	float dashTime;
	float dashTimeMax;
	float dashDecayRate;
	float dashSpeedBoost;
	float dashDelay;
	float dashDelayMax;
	int isDashing;

	float time;

	float fireTime;
	float fireDelay;
	int magazine;

	int alpha;
	float size;
	float oriSize;

	int active;

	UnitType unitType;
	BossState state;
	int phase;
	int sniper;
} Boss;

typedef struct Bullet
{
	CP_Vector projPos;// 투사체 좌표
	float projSpd;// 투사체 속도

	float degree;
	float fireAngle; // 여기부터 렌더러에서 조절
	CP_Vector fireDir;
	CP_Vector direction;

	float size;

	int active;

	int sniper; // 플레이어와 충돌한 미사일
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
Boss elite_StageFive;
Enemy enemy_StageSix;
Enemy enemies[6][MAX_ENEMIES];
Bullet CircleBullets_StageThree[MAX_ENEMIES][CLIP][MAX_BULLETS_PER_ENEMY];
Bullet Bullets_StageOne[MAX_ENEMIES][MAX_BULLETS_PER_ENEMY];
Bullet Bullets_StageSix[MAX_BULLETS_PER_ENEMY];
Laser Lasers_StageTwo[MAX_ENEMIES];

void EnemyInit_BossStage(Boss*);

void EnemyInit_StageOne(Enemy*);
void EnemyMove_StageOne(Enemy*);

void EnemyInit_StageTwo(Enemy*, Laser*);
void LaserInit_StageTwo(Laser*);

void EnemyInit_StageThree(Enemy*);

void EnemyInit_StageFour(Enemy*);
void EnemyMove_StageFour(Enemy*);

void EnemyInit_StageFive(Boss*);
void EnemyMove_StageFive(Boss*);

void EnemyInit_StageSix(Enemy*);
void EnemyMove_StageSix(Enemy*);


void BulletConditioner(Enemy*, Bullet*);
void CircleBulletConditioner(Enemy*, Bullet [CLIP][MAX_BULLETS_PER_ENEMY]);
void CircleBulletFire(Enemy*, Bullet [CLIP][MAX_BULLETS_PER_ENEMY]);
void DirectBulletFire(Enemy*, Bullet*);

Bullet CrossBullets_Boss[4][MAX_BULLETS_PER_ENEMY];
void BossCrossFire(Boss*, Bullet*);

void CreateLaser_StageTwo(Enemy*, Laser*);
void LaserAttack(Laser*);

void EnableBoss(Boss*);
void EnableEnemy(Enemy*);
void DisableEnemy(Enemy*);
void DisableBoss(Boss*);

void ChangeEnemySize();
void BossStageController(Boss* _boss);
