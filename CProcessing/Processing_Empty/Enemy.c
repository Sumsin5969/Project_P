#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Enemy.h"
#include "Defines.h"
#include "MyC/GameManager.h"
#include "MyC/ZoomCamera.h"
#include "MyC/Collision.h"

// 적과 탄환 초기화
// 
void EnemyInit_StageOne(Enemy* _enemy)
{
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		_enemy[i].isAttack = 0;
		_enemy[i].spd = 100.f;
		_enemy[i].size = 50.f;
		_enemy[i].active = 0;
		_enemy[i].fireDelay = 0.7f;
		_enemy[i].fireTime = 0.f;
		_enemy[i].magazine = 0;
		switch (i)
		{
		case 0:
			_enemy[i].pos.x = -850;
			_enemy[i].pos.y = -450;
			_enemy[i].enemyDestination = TOPLEFT;
			break;
		case 1:
			_enemy[i].pos.x = 850;
			_enemy[i].pos.y = -450;
			_enemy[i].enemyDestination = TOPRIGHT;
			break;
		case 2:
			_enemy[i].pos.x = -850;
			_enemy[i].pos.y = 450;
			_enemy[i].enemyDestination = BOTTOMLEFT;
			break;
		case 3:
			_enemy[i].pos.x = 850;
			_enemy[i].pos.y = 450;
			_enemy[i].enemyDestination = BOTTOMRIGHT;
			break;
		}

		for (int j = 0; j < MAX_BULLETS_PER_ENEMY; j++)
		{
			// Todo: 안쓰는 변수가 안생기도록 하는게 더 낫지만, 
			//       MJ 안쓰는 변수라도 초기화 하는 것을 권장
			Bullets_StageOne[i][j].projSpd = 200.f;
			Bullets_StageOne[i][j].projTime = 0.f;
			Bullets_StageOne[i][j].active = 0;
			Bullets_StageOne[i][j].size = 15.f;
		}
	}
}
// 스테이지 2로 넘어갈 시 출현할 적을 gameinit에서 초기화
// Enemy속성들 2행의 1차원 배열로 초기화 할 거임
// todo: 스테이지별 적에게 할당할 탄환 배열 또 만들기
void EnemyInit_StageTwo(Enemy* _enemy, Laser* laser)
{
	// pos x,y는 switch-case로 할 거임
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		_enemy[i].spd = 0.f;
		_enemy[i].fireTime = 0.f;
		_enemy[i].fireDelay = 0.f;
		_enemy[i].size = 50.f;
		_enemy[i].magazine = 0;
		_enemy[i].active = 0;
		switch (i)
		{
		case 0:
			_enemy[i].pos.x = -1055;
			_enemy[i].pos.y = -320;
			break;
		case 1:
			_enemy[i].pos.x = -1055;
			_enemy[i].pos.y = 120;
			break;
		case 2:
			_enemy[i].pos.x = 1055;
			_enemy[i].pos.y = -100;
			break;
		case 3:
			_enemy[i].pos.x = 1055;
			_enemy[i].pos.y = 340;
			break;
		}
		switch (i)
		{
		case 0:
			laser[i].laserDirection = LD_RIGHT;
			break;
		case 1:
			laser[i].laserDirection = LD_LEFT;
			break;
		case 2:
			laser[i].laserDirection = LD_UP;
			break;
		case 3:
			laser[i].laserDirection = LD_DOWN;
			break;
		}
		laser[i].pos.x = _enemy[i].pos.x;
		laser[i].pos.y = _enemy[i].pos.y;
		laser[i].laserAlpha = 50; // 전조 알파값
		laser[i].laserAlphaMax = 200; // 전조 최대 알파값

		laser[i].time = 0;
		laser[i].idleDuration = 2.f;
		laser[i].warningAttackDuration = 1.5f;
		laser[i].waitDuration = 0.5f;
		laser[i].attackDuration = 1.5f;

		laser[i].laserWarningAttackRange = 0.f;
		laser[i].laserWarningAttackRangeMax = _enemy[i].size;

		laser[i].laserWidth = 0.f;
		laser[i].laserHeight = 0.f;

		laser[i].state = IDLE;
	}
}
void EnemyInit_StageThree(Enemy* _enemy)
{
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		_enemy[i].spd = 0.f;
		_enemy[i].fireTime = 0.f;
		_enemy[i].fireDelay = 3.f;
		_enemy[i].size = 50.f;
		_enemy[i].magazine = 0;
		_enemy[i].active = 0;
		switch (i)
		{
		case 0:
			_enemy[i].pos.x = -1320;
			_enemy[i].pos.y = -720;
			break;
		case 1:
			_enemy[i].pos.x = -1320;
			_enemy[i].pos.y = 720;
			break;
		case 2:
			_enemy[i].pos.x = 1320;
			_enemy[i].pos.y = -720;
			break;
		case 3:
			_enemy[i].pos.x = 1320;
			_enemy[i].pos.y = 720;
			break;
		}
		for (int j = 0; j < MAX_ENEMIES; j++)
		{
			for (int k = 0;k < MAX_BULLETS_PER_ENEMY;k++)
			{
				CircleBullets_StageThree[i][j][k].projSpd = 800.f;
				CircleBullets_StageThree[i][j][k].projTime = 0.f;
				CircleBullets_StageThree[i][j][k].degree = j * (360.f / MAX_BULLETS_PER_ENEMY);
				CircleBullets_StageThree[i][j][k].active = 0;
				CircleBullets_StageThree[i][j][k].size = 15.f;
			}
		}
	}
}
// Enemy를 움직여주는 함수: 반시계 방향으로 Enemy를 지속적으로 이동
void EnemyMove_StageOne(Enemy* enemy)
{
	float dt = GetDt() * (enemy->spd);
	switch (enemy->enemyDestination)
	{
	case TOPLEFT:
		enemy->pos.y += dt;
		// Zoom level 1에서 BOTTOMLEFT 적의 y좌표가 450이라서 거기까지 이동
		// 좌표에 zoom level을 곱해서 가변적인 좌표를 얻음
		if (enemy->pos.y >= 450)
		{
			enemy->enemyDestination = BOTTOMLEFT;
		}
		break;
	case BOTTOMLEFT:
		enemy->pos.x += dt * (17.f / 9.f);
		if (enemy->pos.x >= 850)
		{
			enemy->enemyDestination = BOTTOMRIGHT;
		}
		break;
	case BOTTOMRIGHT:
		enemy->pos.y -= dt;
		if (enemy->pos.y <= -450)
		{
			enemy->enemyDestination = TOPRIGHT;
		}
		break;
	case TOPRIGHT:
		enemy->pos.x -= dt * (17.f / 9.f);
		if (enemy->pos.x <= -850)
		{
			enemy->enemyDestination = TOPLEFT;
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
void CircleBulletConditioner(Enemy* e, Bullet* b)
{
	float dt = GetDt();
	e->fireTime += dt;
	for (int i = 0; i < MAX_BULLETS_PER_ENEMY; i++)
	{
		if (e->fireDelay <= e->fireTime)
		{
			e->fireTime = 0.f;
			b[e->magazine].active = 1;
			e->magazine++;
		}
		if (e->magazine >= MAX_ENEMIES)
		{
			e->magazine = 0;
		}
	}
}

// 원형 발사 패턴
// 탄환의 position을 업데이트 해주고 Draw도 해줌
// 탄환의 개수는 MAX_BULLETS_PER_ENEMY 만큼 있어야 함 
void CircleBulletFire(Enemy* e, Bullet* b)
{
	float dt = GetDt();
	for (int i = 0; i < MAX_BULLETS_PER_ENEMY; i++)
	{
		float originX = e->pos.x;
		float originY = e->pos.y;
		if (!b[i].active)
		{
			b[i].projPos.x = originX;
			b[i].projPos.y = originY;
			b[i].fireAngle = CP_Math_Radians(b[i].degree);
			b[i].fireDir.x = cosf(b[i].fireAngle);
			b[i].fireDir.y = sinf(b[i].fireAngle);
		}
		else
		{
			b[i].projPos.x += b[i].projSpd * b[i].fireDir.x * dt;
			b[i].projPos.y += b[i].projSpd * b[i].fireDir.y * dt;
			b[i].degree += 360.f / MAX_BULLETS_PER_ENEMY;
			CP_Settings_Fill(CP_Color_Create(238, 1, 147, 255));
		}
	}
}

// 발사 시점 플레이어 위치로 직진하는 탄환 발사
// 탄환의 position 업데이트 및 탄환 Draw
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
			b[i].direction = CP_Vector_Normalize(b[i].fireDir);
		}
		if (b[i].active)
		{
			// 방향 정규화 할 거임
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
		printf("IDLE 상태 \n");
		laser->laserWarningAttackRange = 0.f;
		laser->time += dt;

		if (laser->idleDuration < laser->time)	// 전조를 쏘겠다.
		{
			laser->state = WARNING;
			laser->time = 0;
		}

	}

	if (laser->state == WARNING)	// 
	{
		printf("WARNING 상태 \n");
		laser->time += dt;
		laser->laserWarningAttackRange += dt * 30.f;
		laser->laserAlpha = (int)((laser->time / laser->warningAttackDuration) * laser->laserAlphaMax);

		if (laser->laserAlpha > laser->laserAlphaMax) // 알파 최대값 넘어가는 것 방지하기위함
		{
			laser->laserAlpha = laser->laserAlphaMax;
		}

		if (laser->laserWarningAttackRange > laser->laserWarningAttackRangeMax)	// 두께가 최대보다 높으면 최대로 만들어주겠다.
		{
			laser->laserWarningAttackRange = laser->laserWarningAttackRangeMax;
		}

		if (laser->warningAttackDuration <= laser->time)
		{
			laser->state = WAIT;
			laser->time = 0;
		}
	}

	if (laser->state == WAIT)
	{
		printf("WAIT 상태 \n");
		laser->time += dt;

		if (laser->waitDuration <= laser->time)	// 딜레이 시간이 다 되면
		{
			laser->state = ATTACK;
			laser->time = 0;
		}
	}

	if (laser->state == ATTACK)
	{
		printf("ATTACK 상태 \n");
		laser->time += dt;

		if (laser->attackDuration <= laser->time)
		{
			laser->state = IDLE;
			laser->time = 0;
		}

	}
}

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

int LaserIsTimeout(Timer timer)
{
	if (timer.time >= timer.timeMax)
		return 1;
	return 0;
}

void DisableEnemy(Enemy* _enemy)
{
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		_enemy[i].active = 0;
	}
}
