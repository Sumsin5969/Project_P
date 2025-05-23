﻿#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Enemy.h"
#include "Defines.h"
#include "MyC/GameManager.h"
#include "MyC/ZoomCamera.h"
#include "MyC/Collision.h"
#include "StageManager.h"

// 사이징 관련
static float pulse = 0.f;
static int shrinking = 1;
const float PERIOD = 1.f;

void InitBoss(Boss* _boss)
{
	_boss->pos.x = 3600.f;
	_boss->pos.y = 0.f;
	_boss->spd = 500.f;
	_boss->dashTime = 0.f;
	_boss->dashTimeMax = 0.3f;
	_boss->dashSpeedBoost = 100.f;
	_boss->dashDelay = 0.f;
	_boss->dashDelayMax = .8f;
	_boss->time = 0.f;//보스스테이지 러닝타임
	_boss->fireTime = 0.f;
	_boss->fireDelay = 0.25f;
	_boss->fireIdleTime = 0.f;
	_boss->magazine = 0;

	_boss->size = 600.f;
	_boss->active = 0;
	_boss->unitType = BOSSCHARACTER;
	_boss->state = APPEAR;
	_boss->phase = 0;
	_boss->isLeft = 0;
	_boss->sniper = 0;
	_boss->cameraAccel = 1.f;
	_boss->cameraMoveTime = 0.f;
	// 보스 스테이지 레이저 초기화
	_boss->rd = 0;
	_boss->rdprev = 0;
	_boss->idleTime = 0;
	_boss->arrIndex = 0;
	_boss->waitTime = 0;
	_boss->laserCycle = 0;
	float timeArray[5] = { 0.56f, 0.45f,0.45f,0.45f,0.3f };
	for (int i = 0; i < 5; i++)
	{
		_boss->timeArr[i] = timeArray[i];
	}
}

void InitBossFragment(Boss* _boss)
{
	for (int i = 0; i < 8; i++)
	{
		BossFragment[i].degree = (360.f / 8) * i;
		BossFragment[i].fireAngle = CP_Math_Radians(BossFragment[i].degree);
		BossFragment[i].fireDir.x = cosf(BossFragment[i].fireAngle);
		BossFragment[i].fireDir.y = sinf(BossFragment[i].fireAngle);
		BossFragment[i].projPos = _boss->pos;
		BossFragment[i].projSpd = 3000.f;
		BossFragment[i].active = 0;
		BossFrag[i].width = _boss->size;
		BossFrag[i].height = _boss->size;
		BossFrag[i].sniper = 0;
	}
}

void InitBossCrossBullet(Boss* _boss)
{
	// Init Bullets
	int dirChanger = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < MAX_BULLETS_PER_ENEMY; j++)
		{
			if (j % 3 == 0 && j != 0)
			{
				if (dirChanger == 0) dirChanger = 1;
				else dirChanger = 0;
			}
			if (dirChanger == 0)
			{
				CrossBullets_Boss[i][j].degree = i * (360.f / 4);
				CrossBullets_Boss[i][j].fireAngle = CP_Math_Radians(CrossBullets_Boss[i][j].degree);
				CrossBullets_Boss[i][j].fireDir.x = cosf(CrossBullets_Boss[i][j].fireAngle);
				CrossBullets_Boss[i][j].fireDir.y = sinf(CrossBullets_Boss[i][j].fireAngle);
			}
			else
			{
				CrossBullets_Boss[i][j].degree = i * (360.f / 4) - 45;
				CrossBullets_Boss[i][j].fireAngle = CP_Math_Radians(CrossBullets_Boss[i][j].degree);
				CrossBullets_Boss[i][j].fireDir.x = cosf(CrossBullets_Boss[i][j].fireAngle);
				CrossBullets_Boss[i][j].fireDir.y = sinf(CrossBullets_Boss[i][j].fireAngle);
			}
			CrossBullets_Boss[i][j].projPos = _boss->pos;
			CrossBullets_Boss[i][j].projSpd = 2600.f;
			CrossBullets_Boss[i][j].active = 0;
			CrossBullets_Boss[i][j].size = _boss->size / 3;
			CrossBullets_Boss[i][j].sniper = 0;
		}
	}
}

void InitBossSpiralBullet(Boss* _boss)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0;j < MAX_BULLETS_PER_ENEMY;j++)
		{
			SpiralBullets_Boss[i][j].degree = i * (360.f / 4);
			SpiralBullets_Boss[i][j].fireAngle = CP_Math_Radians(CrossBullets_Boss[i]->degree);
			SpiralBullets_Boss[i][j].fireDir.x = cosf(CrossBullets_Boss[i]->fireAngle);
			SpiralBullets_Boss[i][j].fireDir.y = sinf(CrossBullets_Boss[i]->fireAngle);
			SpiralBullets_Boss[i][j].projPos = _boss->pos;
			SpiralBullets_Boss[i][j].projSpd = 800.f;
			SpiralBullets_Boss[i][j].active = 0;
			SpiralBullets_Boss[i][j].size = _boss->size / 3;
			SpiralBullets_Boss[i][j].sniper = 0;
		}
	}
}

void InitBossFirstLaserShooter(Enemy* _lasershooter)
{
	float xCoor = -3100;
	for (int i = 0; i < MAX_LASERS; i++)
	{
		xCoor += 6200 / MAX_LASERS;
		_lasershooter[i].pos.x = xCoor;
		_lasershooter[i].pos.y = 3000.f;
		_lasershooter[i].size = 600.f;
		_lasershooter[i].oriSize = _lasershooter[i].size;
		_lasershooter[i].spd = 0.f;
		_lasershooter[i].active = 0;
		_lasershooter[i].sniper = 0;
	}
}

void InitBossFirstLaser(Enemy* _lasershooter, Laser* _laser)
{
	for (int i = 0; i < MAX_LASERS; i++)
	{
		_laser[i].laserDirection = LD_UP;
		_laser[i].pos.x = _lasershooter[i].pos.x;
		_laser[i].pos.y = _lasershooter[i].pos.y;
		_laser[i].laserAlpha = 50;
		_laser[i].laserAlphaMax = 200;

		_laser[i].time = 0.f;
		_laser[i].idleDuration = 0.f;
		_laser[i].warningAttackDuration = 1.f;
		_laser[i].waitDuration = 0.2f;
		_laser[i].attackDuration = 0.5f;

		_laser[i].laserWarningAttackRange = 0.f;
		_laser[i].laserWarningAttackRangeMax = _lasershooter[i].size;

		_laser[i].laserWidth = 0.f;
		_laser[i].laserHeight = 0.f;

		_laser[i].state = IDLE;
		_laser[i].sniper = 0;
		_laser[i].active = 0;
	}
}

void InitBossSecondLaserShooter(Enemy* _lasershooter)
{
	for (int i = 0; i < 3; i++)
	{
		_lasershooter[i].pos.x = -4000;
		switch (i)
		{
		case 0:
			_lasershooter[i].pos.y = -1200.f;
			break;
		case 1:
			_lasershooter[i].pos.y = 0.f;
			break;
		case 2:
			_lasershooter[i].pos.y = 1200.f;
			break;
		}
		_lasershooter[i].size = 1400.f;
		_lasershooter[i].oriSize = _lasershooter[i].size;
		_lasershooter[i].spd = 0.f;
		_lasershooter[i].active = 0;
		_lasershooter[i].sniper = 0;
	}

}

void InitBossSecondLaser(Enemy* _lasershooter, Laser* _laser)
{
	for (int i = 0; i < 3; i++)
	{
		_laser[i].laserDirection = LD_RIGHT;
		_laser[i].pos.x = _lasershooter[i].pos.x;
		_laser[i].pos.y = _lasershooter[i].pos.y;
		_laser[i].laserAlpha = 50;
		_laser[i].laserAlphaMax = 150;

		_laser[i].time = 0.f;
		_laser[i].idleDuration = 3.f;
		_laser[i].warningAttackDuration = 2.f;
		_laser[i].waitDuration = 0.45f;
		_laser[i].attackDuration = 0.6f;

		_laser[i].laserWarningAttackRange = _lasershooter[i].size;
		_laser[i].laserWarningAttackRangeMax = _lasershooter[i].size;

		_laser[i].laserWidth = 0.f;
		_laser[i].laserHeight = 0.f;

		_laser[i].state = IDLE;
		_laser[i].sniper = 0;
		_laser[i].active = 0;
	}
}

void InitBossThirdLaserShooter(Enemy* _lasershooter)
{
	float yCoor = -1650;
	for (int i = 0; i < MAX_LASERS; i++)
	{
		yCoor += 3300 / MAX_LASERS;
		_lasershooter[i].pos.x = 20000;
		_lasershooter[i].pos.y = yCoor;
		_lasershooter[i].size = 500.f;
		_lasershooter[i].oriSize = _lasershooter[i].size;
		_lasershooter[i].spd = 0.f;
		_lasershooter[i].active = 0;
		_lasershooter[i].sniper = 0;
	}

}

void InitBossThirdLaser(Enemy* _lasershooter, Laser* _laser)
{
	for (int i = 0; i < MAX_LASERS; i++)
	{
		_laser[i].laserDirection = LD_RIGHT;
		_laser[i].pos.x = _lasershooter[i].pos.x;
		_laser[i].pos.y = _lasershooter[i].pos.y;
		_laser[i].laserAlpha = 50;
		_laser[i].laserAlphaMax = 200;
		_laser[i].time = 0.f;
		_laser[i].idleDuration = 0.f;
		_laser[i].warningAttackDuration = 1.f;
		_laser[i].waitDuration = 0.2f;
		_laser[i].attackDuration = 0.5f;

		_laser[i].laserWarningAttackRange = 0.f;
		_laser[i].laserWarningAttackRangeMax = _lasershooter[i].size;

		_laser[i].laserWidth = 0.f;
		_laser[i].laserHeight = 0.f;

		_laser[i].state = IDLE;
		_laser[i].sniper = 0;
		_laser[i].active = 0;
	}
}

void InitBossLastLaserShooter(Enemy* _lasershooter)
{
	float xCoor = 25800;
	for (int i = 0; i < 35; i++)
	{
		xCoor += 6200 / 32;
		_lasershooter[i].pos.x = xCoor;
		_lasershooter[i].pos.y = 3000.f;
		_lasershooter[i].size = 200.f;
		_lasershooter[i].oriSize = _lasershooter[i].size;
		_lasershooter[i].spd = 0.f;
		_lasershooter[i].active = 0;
		_lasershooter[i].sniper = 0;
	}
}

void InitBossLastLaser(Enemy* _lasershooter, Laser* _laser)
{
	for (int i = 0; i < 35; i++)
	{
		_laser[i].laserDirection = LD_UP;
		_laser[i].pos.x = _lasershooter[i].pos.x;
		_laser[i].pos.y = _lasershooter[i].pos.y;
		_laser[i].laserAlpha = 50;
		_laser[i].laserAlphaMax = 200;

		_laser[i].time = 0.f;
		_laser[i].idleDuration = 0.f;
		_laser[i].warningAttackDuration = 1.5f;
		_laser[i].waitDuration = 0.f;
		_laser[i].attackDuration = 0.05f;

		_laser[i].laserWarningAttackRange = _lasershooter[i].size;
		_laser[i].laserWarningAttackRangeMax = _lasershooter[i].size;

		_laser[i].laserWidth = 0.f;
		_laser[i].laserHeight = 0.f;

		_laser[i].state = IDLE;
		_laser[i].sniper = 0;
		_laser[i].active = 0;
	}
}

// 스테이지 1 적과 탄환 초기화
void EnemyInit_StageOne(Enemy* _enemy)
{
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		_enemy[i].spd = 100.f;
		_enemy[i].size = 50.f;
		_enemy[i].oriSize = 50.f;
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

		// Init Bullets
		for (int j = 0; j < MAX_BULLETS_PER_ENEMY; j++)
		{
			// Todo: 안쓰는 변수가 안생기도록 하는게 더 낫지만, 
			//       MJ 안쓰는 변수라도 초기화 하는 것을 권장
			Bullets_StageOne[i][j].projSpd = 300.f;
			Bullets_StageOne[i][j].active = 0;
			Bullets_StageOne[i][j].size = _enemy->size / 3;
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
		_enemy[i].oriSize = 50.f * 1.25f;
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
		_enemy[i].size = 50.f * 1.25f * 1.25f;
		_enemy[i].oriSize = 50.f * 1.25f * 1.25f;
		_enemy[i].magazine = 0;
		_enemy[i].active = 0;
		_enemy[i].sniper = 0;
		switch (i)
		{
		case 0:
			_enemy[i].pos.x = -1330;
			_enemy[i].pos.y = -715;
			break;
		case 1:
			_enemy[i].pos.x = -1330;
			_enemy[i].pos.y = 715;
			break;
		case 2:
			_enemy[i].pos.x = 1330;
			_enemy[i].pos.y = -715;
			break;
		case 3:
			_enemy[i].pos.x = 1330;
			_enemy[i].pos.y = 715;
			break;
		}

		// Init Bullets
		for (int j = 0; j < CLIP; j++)
		{
			for (int k = 0;k < MAX_BULLETS_PER_ENEMY;k++)
			{
				CircleBullets_StageThree[i][j][k].projPos = _enemy[i].pos;
				CircleBullets_StageThree[i][j][k].projSpd = 200.f;
				CircleBullets_StageThree[i][j][k].degree = k * (360.f / MAX_BULLETS_PER_ENEMY);
				CircleBullets_StageThree[i][j][k].active = 0;
				CircleBullets_StageThree[i][j][k].size = _enemy->size / 3;
				CircleBullets_StageThree[i][j][k].sniper = 0;
			}
		}
	}
}

// 스테이지 4 적과 탄환 초기화
void EnemyInit_StageFour(Enemy* _enemy)
{
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		_enemy[i].active = 0;
		_enemy[i].fireDelay = 1.f;
		_enemy[i].fireTime = 0.f;
		_enemy[i].pos.x = 0.f;
		_enemy[i].pos.y = 0.f;
		_enemy[i].size = 50.f * 1.25f * 1.25f * 1.25f;
		_enemy[i].oriSize = 50.f * 1.25f * 1.25f * 1.25f;
		_enemy[i].spd = 200.f;
		_enemy[i].sniper = 0;
		_enemy[i].unitType = ENEMYCHARACTER;
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

// 스테이지 5 적 초기화
void EnemyInit_StageFive(Boss* _elite)
{
	_elite->pos.x = 1900.f;
	_elite->pos.y = 0.f;
	_elite->size = 50.f * (float)pow(1.25, 4);
	_elite->oriSize = 50.f * (float)pow(1.25, 4);
	_elite->dashTime = 0.f;
	_elite->dashTimeMax = .3f;
	_elite->dashSpeedBoost = 40.f;
	_elite->dashDelay = 0.f;
	_elite->dashDelayMax = 3.f;
	_elite->isDashing = 0;
	_elite->spd = 0.f;
	_elite->active = 0;
	_elite->sniper = 0;
	_elite->unitType = ENEMYCHARACTER;
}

//스테이지 6 적 초기화
void EnemyInit_StageSix(Enemy* _enemy)
{
	_enemy->pos.x = -2200.f;
	_enemy->pos.y = -1200.f;
	_enemy->enemyDestination = TOPLEFT;
	_enemy->spd = 1500.f;
	_enemy->fireTime = 0.f;
	_enemy->fireDelay = 3.f;
	_enemy->size = 50.f * (float)pow(1.25, 5);
	_enemy->oriSize = 50.f * (float)pow(1.25, 5);
	_enemy->magazine = 0;
	_enemy->active = 0;
	_enemy->sniper = 0;

	// Init Bullets
	for (int i = 0; i < MAX_BULLETS_PER_ENEMY; i++)
	{
		Bullets_StageSix[i].projPos = _enemy->pos;
		Bullets_StageSix[i].projSpd = 2500.f;
		Bullets_StageSix[i].active = 0;
		Bullets_StageSix[i].size = _enemy->size / 3;
		Bullets_StageSix[i].sniper = 0;
	}
}

// 스테이지 1 적 반시계 방향으로 지속적으로 이동
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

// 스테이지4 적 대각선으로 움직이는 함수
void EnemyMove_StageFour(Enemy* _enemy)
{
	float dt = GetDt() * (_enemy->spd);
	float leftEnd = -1800.f;
	float rightEnd = 1800.f;
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

// 스테이지5 적 대쉬 함수
void EnemyMove_StageFive(Boss* _elite)
{
	float dt = GetDt();
	static float saveEnemyShadowTimer = 0.f; // 잔상 남기기 타이머
	_elite->dashDelay += dt;

	if (_elite->dashDelay >= _elite->dashDelayMax && !_elite->isDashing)
	{
		//대쉬 ㄱㄱ
		_elite->isDashing = 1;
		_elite->spd += _elite->dashSpeedBoost;
		_elite->dashDir = CP_Vector_Subtract(player->pos, _elite->pos);
		_elite->dashDir = CP_Vector_Normalize(_elite->dashDir);
		_elite->dashDecayRate = _elite->dashSpeedBoost / _elite->dashTimeMax;
	}

	if (_elite->isDashing)
	{
		saveEnemyShadowTimer += dt;

		if (saveEnemyShadowTimer >= 0.03f)
		{
			SaveEnemyPos();
			saveEnemyShadowTimer = 0.f;
		}
		_elite->dashTime += dt;
		_elite->pos.x += _elite->dashDir.x * _elite->spd;
		_elite->pos.y += _elite->dashDir.y * _elite->spd;
		_elite->spd -= dt * _elite->dashDecayRate;

		if (_elite->dashTime >= _elite->dashTimeMax)
		{
			enemyShadowIndex = 0;
			_elite->dashTime = 0.f;
			_elite->dashDelay = 0.f;
			_elite->isDashing = 0;
			_elite->spd = 0.f;
		}
	}
}

// 스테이지6 적 움직이는 함수
void EnemyMove_StageSix(Enemy* _enemy)
{
	float dt = GetDt() * _enemy->spd;
	float leftEnd = -2200.f;
	float rightEnd = 2200.f;
	float topEnd = -1200.f;
	float bottomEnd = 1200.f;
	switch (_enemy->enemyDestination)
	{
	case TOPLEFT:
		_enemy->pos.y += dt;
		if (_enemy->pos.y >= bottomEnd)
		{
			_enemy->enemyDestination = BOTTOMLEFT;
		}
		break;
	case BOTTOMLEFT:
		_enemy->pos.x += dt;
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
		_enemy->pos.x -= dt;
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

// 발사 시점 플레이어 위치로 직진하는 탄환 발사
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
		float t = laser->time / laser->warningAttackDuration;
		if (t > 1.f) t = 1.f;

		if (laser->laserAlpha < laser->laserAlphaMax)
		{
			laser->laserAlpha = (int)(laser->laserAlphaMax * t);
		}
		else
		{
			laser->laserAlpha = laser->laserAlphaMax; // 알파 최대값 넘어가는 것 방지하기위함
		}

		if (laser->laserWarningAttackRange < laser->laserWarningAttackRangeMax)
		{
			laser->laserWarningAttackRange = laser->laserWarningAttackRangeMax * t;
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
			StartCameraShake(.06f);
		}
	}

	if (laser->state == ATTACK)
	{
		laser->laserAlpha = 0;
		laser->time += dt;

		if (laser->attackDuration <= laser->time)
		{
			laser->state = IDLE;
			laser->active = 0;
			laser->time = 0;
		}

	}
}

void LaserAttack_Circle(LaserCircle* laser)
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

		float t = laser->time / laser->warningAttackDuration;
		if (t > 1.f) t = 1.f;

		if (laser->laserAlpha < laser->laserAlphaMax)
		{
			laser->laserAlpha = (int)(laser->laserAlphaMax * t);
		}
		else
		{
			laser->laserAlpha = laser->laserAlphaMax; // 알파 최대값 넘어가는 것 방지하기위함
		}

		if (laser->laserWarningAttackRange < laser->laserWarningAttackRangeMax)
		{
			laser->laserWarningAttackRange = laser->laserWarningAttackRangeMax * t;
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
			laser->active = 0;
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
		ex = worldLeft / cam->camZoom;        // 진짜 왼쪽 끝
		sy = ey = e->pos.y;
		len = sx - ex;
		break;

	case LD_RIGHT:
		sx = e->pos.x + e->size * 0.5f;
		ex = worldRight / cam->camZoom;       // 진짜 오른쪽 끝
		sy = ey = e->pos.y;
		len = ex - sx;
		break;

	case LD_UP:
		sy = e->pos.y - e->size * 0.5f;
		ey = worldBottom / cam->camZoom;      // 진짜 아래쪽 끝
		sx = ex = e->pos.x;
		len = sy - ey;
		break;

	case LD_DOWN:
		sy = e->pos.y + e->size * 0.5f;
		ey = worldTop / cam->camZoom;         // 진짜 위쪽 끝
		sx = ex = e->pos.x;
		len = ey - sy;
		break;
	}

	// 중앙 위치 & 크기 설정
	laser->pos.x = (sx + ex) * 0.5f;
	laser->pos.y = (sy + ey) * 0.5f;

	if (laser->laserDirection == LD_LEFT ||
		laser->laserDirection == LD_RIGHT)
	{
		laser->laserWidth = len;
		laser->laserHeight = e->oriSize;
	}
	else
	{
		laser->laserWidth = e->oriSize;
		laser->laserHeight = len;
	}
}

//void CreateLaser_Circle(LaserCircle* laser, float duration) // Todo
//{
//	CamInfo camInfo = *GetCamera();
//	CP_Vector camPos = camInfo.camPos;
//	float HorizonMin = WIDTH / camInfo.camZoom - camPos.x;
//	float HorizonMax = WIDTH / camInfo.camZoom + camPos.x;
//	float VerticalMin = HEIGHT / camInfo.camZoom + camPos.y;
//	float VerticalMax = HEIGHT / camInfo.camZoom - camPos.y;
//
//	/// duration동안 laserCircle을 생성해준다.
//	/// 생성위치는 카메라 좌표기
//}

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

void ChangeEnemySize()
{
	float dt = GetDt();
	float half = PERIOD * 0.5f;
	float delta = dt / half;

	if (shrinking == 1)
	{
		pulse -= delta;
		if (pulse <= 0.f)
		{
			pulse = 0.f;
			shrinking = 0;
		}
	}
	else
	{
		pulse += delta;
		if (1.0f <= pulse)
		{
			pulse = 1.f;
			shrinking = 1;
		}
	}

	float scale = 0.9f + 0.1f * pulse;	// 최소 0.9f / 최대 0.9f + 0.1f;

	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < MAX_ENEMIES; ++j)
		{
			enemies[i][j].size = enemies[i][j].oriSize * scale;
		}
	}

}

void LaserParticleInit_StageTwo(Laser* enemy, LaserParticle* lp,Enemy* father)
{
	lp->myFather = father;
	lp->myMother = enemy;
	float rd = rand() % 10 + 1.f;
	lp->length = rd*0.2f;
	//if (rd >= 5.f) rd+=5;
	lp->speed = rd*0.5f;

	lp->pos.x = lp->myFather->pos.x + (rand() % 250 - 125);
	lp->pos.y = lp->myMother->pos.y + (rand() % 250 - 125);
	lp->oriPos = lp->pos;

	lp->angle = CP_Vector_DotProduct(lp->pos, lp->myFather->pos);
}

void LaserParticleMove(LaserParticle* lp)
{
	// 이동시켜준다.
	float distance = CP_Vector_Distance(lp->pos, lp->myFather->pos);


	CP_Vector tempVector = CP_Vector_Subtract(lp->myFather->pos, lp->pos);
	CP_Vector dir = CP_Vector_Normalize(tempVector);

	CP_Vector moveDelta = CP_Vector_Scale(dir, lp->speed);

	lp->pos = CP_Vector_Add(lp->pos, moveDelta); // 이동시키는 함수
	if (distance < 5)
	{
		lp->pos = lp->oriPos;
	}
}