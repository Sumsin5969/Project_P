#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Enemy.h"
#include "Defines.h"
#include "MyC/GameManager.h"
#include "MyC/ZoomCamera.h"
#include "MyC/Collision.h"
#include "StageManager.h"

void EnemyInit_BossStage(Boss* _boss)
{
	//CamInfo* cam = GetCamera();
	//float z = cam->camZoom;

	// 화면 경계(스크린 좌표) → 월드 좌표 역변환
	//float worldLeft = (0 - cam->camPos.x) / z;
	//float worldRight = (WIDTH - cam->camPos.x) / z;
	//float worldTop = (HEIGHT - cam->camPos.y) / z;
	//float worldBottom = (0 - cam->camPos.y) / z;

	_boss->pos.x = 50.f;
	_boss->pos.y = 0.f;
	_boss->size = 200.f;
	_boss->active = 0;
	_boss->sniper = 0;
	_boss->unitType = BOSSCHARACTER;
}

// 스테이지 1 적과 탄환 초기화
void EnemyInit_StageOne(Enemy* _enemy)
{
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		_enemy[i].spd = 100.f;
		_enemy[i].size = 50.f;
		_enemy[i].active = 0;
		_enemy[i].fireDelay = 2.f;
		_enemy[i].fireTime = 0.f;
		_enemy[i].magazine = 0;
		_enemy[i].sniper = 0;
		switch (i)
		{
		case 0:
			_enemy[i].pos.x = -835;
			_enemy[i].pos.y = -450;
			_enemy[i].enemyDestination = TOPLEFT;
			break;
		case 1:
			_enemy[i].pos.x = 835;
			_enemy[i].pos.y = -450;
			_enemy[i].enemyDestination = TOPRIGHT;
			break;
		case 2:
			_enemy[i].pos.x = -835;
			_enemy[i].pos.y = 450;
			_enemy[i].enemyDestination = BOTTOMLEFT;
			break;
		case 3:
			_enemy[i].pos.x = 835;
			_enemy[i].pos.y = 450;
			_enemy[i].enemyDestination = BOTTOMRIGHT;
			break;
		}

		for (int j = 0; j < MAX_BULLETS_PER_ENEMY; j++)
		{
			// Todo: 안쓰는 변수가 안생기도록 하는게 더 낫지만, 
			//       MJ 안쓰는 변수라도 초기화 하는 것을 권장
			Bullets_StageOne[i][j].projSpd = 300.f;
			Bullets_StageOne[i][j].projTime = 0.f;
			Bullets_StageOne[i][j].active = 0;
			Bullets_StageOne[i][j].size = 15.f;
			Bullets_StageOne[i][j].sniper = 0;
		}
	}
}

// 스테이지 2 적과 레이저 초기화
void EnemyInit_StageTwo(Enemy* _enemy, Laser* laser)
{
	// pos x,y는 switch-case로 할 거임
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		_enemy[i].spd = 0.f;
		_enemy[i].fireTime = 0.f;
		_enemy[i].fireDelay = 0.f;
		_enemy[i].size = 50.f * 1.25f;
		_enemy[i].magazine = 0;
		_enemy[i].active = 0;
		_enemy[i].sniper = 0;
		switch (i)
		{
		case 0:
			_enemy[i].pos.x = -1055;
			_enemy[i].pos.y = -420;
			break;
		case 1:
			_enemy[i].pos.x = -1055;
			_enemy[i].pos.y = 220;
			break;
		case 2:
			_enemy[i].pos.x = 1055;
			_enemy[i].pos.y = -200;
			break;
		case 3:
			_enemy[i].pos.x = 1055;
			_enemy[i].pos.y = 440;
			break;
		}
		switch (i)
		{
		case 0:
			laser[i].laserDirection = LD_RIGHT;
			break;
		case 1:
			laser[i].laserDirection = LD_RIGHT;
			break;
		case 2:
			laser[i].laserDirection = LD_LEFT;
			break;
		case 3:
			laser[i].laserDirection = LD_LEFT;
			break;
		}
		laser[i].pos.x = _enemy[i].pos.x;
		laser[i].pos.y = _enemy[i].pos.y;
		laser[i].laserAlpha = 50; // 전조 알파값
		laser[i].laserAlphaMax = 200; // 전조 최대 알파값

		laser[i].time = 0;
		laser[i].idleDuration = 4.f;
		laser[i].warningAttackDuration = 1.5f;
		laser[i].waitDuration = 0.5f;
		laser[i].attackDuration = 1.0f;

		laser[i].laserWarningAttackRange = 0.f;
		laser[i].laserWarningAttackRangeMax = _enemy[i].size;

		laser[i].laserWidth = 0.f;
		laser[i].laserHeight = 0.f;

		laser[i].state = IDLE;
		laser[i].sniper = 0;

	}
}

// 스테이지 3 적과 탄환 초기화
void EnemyInit_StageThree(Enemy* _enemy)
{
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		_enemy[i].spd = 0.f;
		_enemy[i].fireTime = 0.f;
		_enemy[i].fireDelay = 5.f;
		_enemy[i].size = (50.f * 1.25f) * 1.25f;
		_enemy[i].magazine = 0;
		_enemy[i].active = 0;
		_enemy[i].sniper = 0;
		switch (i)
		{
		case 0:
			_enemy[i].pos.x = -1310;
			_enemy[i].pos.y = -710;
			break;
		case 1:
			_enemy[i].pos.x = -1310;
			_enemy[i].pos.y = 710;
			break;
		case 2:
			_enemy[i].pos.x = 1310;
			_enemy[i].pos.y = -710;
			break;
		case 3:
			_enemy[i].pos.x = 1310;
			_enemy[i].pos.y = 710;
			break;
		}
		for (int j = 0; j < CLIP; j++)
		{
			for (int k = 0;k < MAX_BULLETS_PER_ENEMY;k++)
			{
				CircleBullets_StageThree[i][j][k].projPos = _enemy[i].pos;
				CircleBullets_StageThree[i][j][k].projSpd = 200.f;
				CircleBullets_StageThree[i][j][k].projTime = 0.f;
				CircleBullets_StageThree[i][j][k].degree = k * (360.f / MAX_BULLETS_PER_ENEMY);
				CircleBullets_StageThree[i][j][k].active = 0;
				CircleBullets_StageThree[i][j][k].size = _enemy->size / 3;
				CircleBullets_StageThree[i][j][k].sniper = 0;
			}
		}
	}
}

// 스테이지 3 적과 탄환 초기화
void EnemyInit_StageFour(Enemy* _enemy)
{
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		_enemy[i].active = 0;
		_enemy[i].fireDelay = 1.f;
		_enemy[i].fireTime = 0.f;
		_enemy[i].pos.x = 0.f;
		_enemy[i].pos.y = 0.f;
		_enemy[i].size = ((50.f * 1.25f) * 1.25f) * 1.25f;
		_enemy[i].oriSize = ((50.f * 1.25f) * 1.25f) * 1.25f;
		_enemy[i].spd = 200.f;
		_enemy[i].sniper = 0;
		switch (i)
		{
		case 0:
			_enemy[i].pos.x = -1600.f;
			_enemy[i].pos.y = -850.f;
			_enemy[i].enemyDestination = TOPLEFT;
			break;
		case 1:
			_enemy[i].pos.x = 1600.f;
			_enemy[i].pos.y = -850.f;
			_enemy[i].enemyDestination = TOPRIGHT;
			break;
		case 2:
			_enemy[i].pos.x = -1600.f;
			_enemy[i].pos.y = 850.f;
			_enemy[i].enemyDestination = BOTTOMLEFT;
			break;
		case 3:
			_enemy[i].pos.x = 1600.f;
			_enemy[i].pos.y = 850.f;
			_enemy[i].enemyDestination = BOTTOMRIGHT;
			break;
		}
	}
}
// Enemy를 움직여주는 함수: 반시계 방향으로 Enemy를 지속적으로 이동
void EnemyMove_StageOne(Enemy* _enemy)
{
	float dt = GetDt() * (_enemy->spd);
	float leftEnd = -835.f;
	float rightEnd = 835.f;
	float topEnd = -450.f;
	float bottomEnd = 450.f;
	switch (_enemy->enemyDestination)
	{
	case TOPLEFT:
		_enemy->pos.y += dt;
		// Zoom level 1에서 BOTTOMLEFT 적의 y좌표가 450이라서 거기까지 이동
		if (_enemy->pos.y >= bottomEnd)
		{
			_enemy->enemyDestination = BOTTOMLEFT;
		}
		break;
	case BOTTOMLEFT:
		_enemy->pos.x += dt * (17.f / 9.f);
		if (_enemy->pos.x >= rightEnd)
		{
			_enemy->enemyDestination = BOTTOMRIGHT;
		}
		break;
	case BOTTOMRIGHT:
		_enemy->pos.y -= dt;
		if (_enemy->pos.y <= topEnd)
		{
			_enemy->enemyDestination = TOPRIGHT;
		}
		break;
	case TOPRIGHT:
		_enemy->pos.x -= dt * (17.f / 9.f);
		if (_enemy->pos.x <= leftEnd)
		{
			_enemy->enemyDestination = TOPLEFT;
		}
		break;
	}
}

// 스테이지4 적 움직임 담당 함수
void EnemyMove_StageFour(Enemy* _enemy)
{
	float dt = GetDt() * (_enemy->spd);
	float leftEnd = -1600.f;
	float rightEnd = 850.f;
	switch (_enemy->enemyDestination)
	{
	case TOPLEFT:
		// 오른쪽 아래로
		_enemy->pos.x += dt * (17.f / 9.f);
		_enemy->pos.y += dt;
		if (_enemy->pos.x >= rightEnd)
		{
			_enemy->enemyDestination = BOTTOMRIGHT;
		}
		break;
	case TOPRIGHT:
		// 왼쪽 아래로
		_enemy->pos.x -= dt * (17.f / 9.f);
		_enemy->pos.y += dt;
		if (_enemy->pos.x <= leftEnd)
		{
			_enemy->enemyDestination = BOTTOMLEFT;
		}
		break;
	case BOTTOMLEFT:
		// 오른쪽 위로
		_enemy->pos.x += dt * (17.f / 9.f);
		_enemy->pos.y -= dt;
		if (_enemy->pos.x >= rightEnd)
		{
			_enemy->enemyDestination = TOPRIGHT;
		}
		break;
	case BOTTOMRIGHT:
		// 왼쪽 위로
		_enemy->pos.x -= dt * (17.f / 9.f);
		_enemy->pos.y -= dt;
		if (_enemy->pos.x <= leftEnd)
		{
			_enemy->enemyDestination = TOPLEFT;
		}
		break;
	}
}

// 시간을 재서 Time > Delay면 탄을 발사하는 함수 만들거임
void BulletConditioner(Enemy* e, Bullet* b)
{
	float dt = GetDt();
	e->fireTime += dt;
	if (e->fireDelay <= e->fireTime)
	{
		e->fireTime = 0.f;
		b[e->magazine].active = 1;
		e->magazine++;

	}
	if (e->magazine >= MAX_BULLETS_PER_ENEMY)
	{
		e->magazine = 0;
	}
}

// 위 함수와 비슷한 역할: 방사형 투사체에 사용됨
void CircleBulletConditioner(Enemy* e, Bullet b[CLIP][MAX_BULLETS_PER_ENEMY])
{
	float dt = GetDt();
	e->fireTime += dt;

	if (e->fireDelay <= e->fireTime)
	{
		//printf("%s %d enemy %p magazine %d\n", __FUNCTION__, __LINE__, e, e->magazine);
		int allInactive = 1;	// 일단 allInactive로 만든다.

		for (int i = 0; i < MAX_BULLETS_PER_ENEMY; i++)	// 한탄창의 max만큼 for문을 돌린다.
		{
			if (b[e->magazine][i].active)	// 해당 탄창중 하나라도 active이면 그 탄창은 쓸수 없다.								  // b[enemy][magazine][bullet] / enemy의 magazin index 번째의 i번째의 탄환이 active라면! 
			{
				allInactive = 0;
				e->magazine++;	// 위에서 쓸 수 없으니까 다음탄창으로 가겠다.
				return;
			}
		}


		if (allInactive)		// (온전한탄창) 쓸 수 있는 탄창이라면
		{
			//printf("%s %d enemy %p magazine %d\n", __FUNCTION__, __LINE__, e, e->magazine);
			for (int i = 0; i < MAX_BULLETS_PER_ENEMY; i++)		// 탄창의 들어있는 탄환만큼 반복하겠다.
			{
				b[e->magazine][i].active = 1;		// 탄환 하나를 활성화
				b[e->magazine][i].degree = i * (360.0f / MAX_BULLETS_PER_ENEMY);	// 각도 설정
			}

			if (e->magazine >= CLIP)		// 탄창의 인덱스가 최대가되면 0으로 바꾸어준다.
			{
				e->magazine = 0;
			}
		}
		e->fireTime = 0.0f;
	}
}

// 원형 발사 패턴
// 탄환의 position을 업데이트
// 탄환의 개수는 MAX_BULLETS_PER_ENEMY 만큼 있어야 함 
void CircleBulletFire(Enemy* e, Bullet b[CLIP][MAX_BULLETS_PER_ENEMY])
{
	float dt = GetDt();
	for (int i = 0; i < CLIP; i++)
	{
		float originX = e->pos.x;
		float originY = e->pos.y;
		for (int j = 0; j < MAX_BULLETS_PER_ENEMY; j++)
		{
			if (!b[i][j].active)
			{
				b[i][j].projPos.x = originX;
				b[i][j].projPos.y = originY;

				b[i][j].fireAngle = CP_Math_Radians(b[i][j].degree);
				b[i][j].fireDir.x = cosf(b[i][j].fireAngle);
				b[i][j].fireDir.y = sinf(b[i][j].fireAngle);
			}
			else
			{
				b[i][j].projPos.x += b[i][j].projSpd * b[i][j].fireDir.x * dt;
				b[i][j].projPos.y += b[i][j].projSpd * b[i][j].fireDir.y * dt;
				CP_Settings_Fill(ENEMY_COLOR());
			}
		}
	}
}

// 발사 시점 플레이어 위치로 직진하는 탄환 발사
// 탄환의 position 업데이트
// e: 탄환의 origin position, 발사 방향을 구하기 위한 Enemy 정보
// b: Enemy.c에서 초기화한 탄환 배열: 탄환의 position 업데이트, position 기반 렌더링에 사용할
//탄환 정보
void DirectBulletFire(Enemy* e, Bullet* b)
{
	float dt = GetDt();

	for (int i = 0; i < MAX_BULLETS_PER_ENEMY; i++)
	{
		if (!b[i].active)
		{
			b[i].projPos.x = e->pos.x;
			b[i].projPos.y = e->pos.y;
			b[i].fireDir = CP_Vector_Subtract(player->pos, e->pos);
			// 방향 정규화 할 거임
			b[i].direction = CP_Vector_Normalize(b[i].fireDir);
		}
		if (b[i].active)
		{
			b[i].projPos.x += b[i].projSpd * b[i].direction.x * dt;
			b[i].projPos.y += b[i].projSpd * b[i].direction.y * dt;
		}
	}
}
void LaserAttack(Laser* laser)
{
	float dt = GetDt();

	if (laser->state == IDLE) // 기본상태
	{
		laser->laserWarningAttackRange = 0.f;
		laser->time += dt;

		if (laser->idleDuration < laser->time)	// 전조를 쏘겠다.
		{
			laser->laserAlpha = 0;
			laser->laserWarningAttackRange = 0;
			laser->time = 0;
			laser->state = WARNING;
		}

	}

	if (laser->state == WARNING)	// 
	{
		laser->time += dt;

		if (laser->laserAlpha < laser->laserAlphaMax)
		{
			laser->laserAlpha = (int)((laser->time / laser->warningAttackDuration) * laser->laserAlphaMax);
		}
		else
		{
			laser->laserAlpha = laser->laserAlphaMax; // 알파 최대값 넘어가는 것 방지하기위함
		}

		if (laser->laserWarningAttackRange < laser->laserWarningAttackRangeMax)
		{
			laser->laserWarningAttackRange += dt * 50.f;
		}
		else
		{
			laser->laserWarningAttackRange = laser->laserWarningAttackRangeMax;	// 두께가 최대보다 높으면 최대로 만들어주겠다.
		}

		if (laser->warningAttackDuration <= laser->time)
		{
			laser->state = WAIT;
			laser->time = 0;
		}
	}

	if (laser->state == WAIT)
	{
		laser->time += dt;

		if (laser->waitDuration <= laser->time)	// 딜레이 시간이 다 되면
		{
			laser->state = ATTACK;
			laser->time = 0;
		}
	}

	if (laser->state == ATTACK)
	{
		laser->laserAlpha = 0;
		laser->time += dt;

		if (laser->attackDuration <= laser->time)
		{
			laser->state = IDLE;
			laser->time = 0;
		}

	}
}
// 레이저 위치 설정해주는 함수
void CreateLaser(Enemy* e, Laser* laser)
{
	CamInfo* cam = GetCamera();
	float z = cam->camZoom;

	// 화면 경계(스크린 좌표) → 월드 좌표 역변환
	float worldLeft = (0 - cam->camPos.x) / z;
	float worldRight = (WIDTH - cam->camPos.x) / z;
	float worldTop = (HEIGHT - cam->camPos.y) / z;
	float worldBottom = (0 - cam->camPos.y) / z;

	float sx = 0.f, sy = 0.f, ex = 0.f, ey = 0.f, len = 0.f;

	switch (laser->laserDirection)
	{
	case LD_LEFT:
		sx = e->pos.x - e->size * 0.5f;
		ex = worldLeft;        // 진짜 왼쪽 끝
		sy = ey = e->pos.y;
		len = sx - ex;
		break;

	case LD_RIGHT:
		sx = e->pos.x + e->size * 0.5f;
		ex = worldRight;       // 진짜 오른쪽 끝
		sy = ey = e->pos.y;
		len = ex - sx;
		break;

	case LD_UP:
		sy = e->pos.y + e->size * 0.5f;
		ey = worldTop;         // 진짜 위쪽 끝
		sx = ex = e->pos.x;
		len = ey - sy;
		break;

	case LD_DOWN:
		sy = e->pos.y - e->size * 0.5f;
		ey = worldBottom;      // 진짜 아래쪽 끝
		sx = ex = e->pos.x;
		len = sy - ey;
		break;
	}

	// 중앙 위치 & 크기 설정
	laser->pos.x = (sx + ex) * 0.5f;
	laser->pos.y = (sy + ey) * 0.5f;

	if (laser->laserDirection == LD_LEFT ||
		laser->laserDirection == LD_RIGHT)
	{
		laser->laserWidth = len;
		laser->laserHeight = e->size;
	}
	else
	{
		laser->laserWidth = e->size;
		laser->laserHeight = len;
	}
}

void EnableEnemy(Enemy* _enemy)
{
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		_enemy[i].active = 1;
	}
}

void DisableEnemy(Enemy* _enemy)
{
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		_enemy[i].active = 0;
	}
}

void EnableBoss(Boss* _boss)
{
	_boss->active = 1;
}

void DisableBoss(Boss* _boss)
{
	_boss->active = 0;
}

void BossStage(Boss* _boss)
{
	if (stageTime == 27.f)
	{
		DisableBoss(&boss);
	}
}