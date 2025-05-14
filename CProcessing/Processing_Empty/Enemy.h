#pragma once
#include "cprocessing.h"
#include "Defines.h"
#include "Obstacle.h"

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
	float fireIdleTime;
	int magazine;

	int alpha;
	float size;
	float oriSize;

	int active;

	UnitType unitType;
	BossState state;
	int isLeft;
	int isMove;
	int phase;
	int sniper;

	//보스전 카메라용 변수
	float cameraAccel;
	float cameraMoveTime;

	// 보스용 레이저 변수
	int rd;
	int rdprev;
	float waitTime; // 첫 레이저 대기시간
	float idleTime; //레이저 발사간격
	int arrIndex; // 발사간격 MAX 배열
	float timeArr[5];
	int laserCycle;
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
	int active;

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

typedef struct LaserCircle
{
	CP_Vector pos;
	int laserAlpha;
	int laserAlphaMax;
	int active;

	float time;

	float idleDuration;
	float warningAttackDuration; // 경고사격 지속시간
	float waitDuration; // 경고사격 후 딜레이 (진짜 사격전 딜레이)
	float attackDuration;

	float laserWarningAttackRange;
	float laserWarningAttackRangeMax;

	float laserSize;

	LaserState state;
	int sniper;
} LaserCircle;

Boss boss;

void InitBoss(Boss*);
void InitBossCrossBullet(Boss*);
void InitBossSpiralBullet(Boss*);

void InitBossFirstLaserShooter(Enemy* _lasershooter);
void InitBossFirstLaser(Enemy* _lasershooter, Laser* _laser);

void InitBossSecondLaserShooter(Enemy*);
void InitBossSecondLaser(Enemy*, Laser*);

void InitBossThirdLaserShooter(Enemy* _lasershooter);
void InitBossThirdLaser(Enemy* _lasershooter, Laser* _laser);

Bullet CrossBullets_Boss[4][MAX_BULLETS_PER_ENEMY];
Bullet SpiralBullets_Boss[4][MAX_BULLETS_PER_ENEMY];

Enemy BossFirstLaserShooter[MAX_LASERS];
Laser FirstLasers_BossStage[MAX_LASERS];

Enemy BossSecondLaserShooter[3];
Laser SecondLasers_BossStage[3];

Enemy BossThirdLaserShooter[MAX_LASERS];
Laser ThirdLasers_BossStage[MAX_LASERS];

Boss elite_StageFive;
Enemy enemy_StageSix;
Enemy enemies[6][MAX_ENEMIES];
Bullet CircleBullets_StageThree[MAX_ENEMIES][CLIP][MAX_BULLETS_PER_ENEMY];
Bullet Bullets_StageOne[MAX_ENEMIES][MAX_BULLETS_PER_ENEMY];
Bullet Bullets_StageSix[MAX_BULLETS_PER_ENEMY];
Laser Lasers_StageTwo[MAX_ENEMIES];

Bullet BossFragment[8];
Obstacle BossFrag[8];
void InitBossFragment(Boss*);

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

void CreateLaser(Enemy*, Laser*);
void LaserAttack(Laser*);
void LaserAttack_StageBoss(Laser*);
void EnableEnemy(Enemy*);
void DisableEnemy(Enemy*);

void ChangeEnemySize();
