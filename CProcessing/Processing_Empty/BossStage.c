#include "cprocessing.h"
#include "MyC/PP_Renderer.h"
#include "MyC/ZoomCamera.h"
#include "Defines.h"
#include "stdio.h"
#include <stdlib.h>
#include "MyC/GameManager.h"
#include "MyC/Collision.h"
#include "MyC/JhDebug.h"
#include "StageManager.h"
#include "Enemy.h"

void CrossBulletConditioner(Boss* _boss)
{
	float dt = GetDt();
	const float fireIdleTimeMax = 1.7f;
	_boss->fireTime += dt;

	if (_boss->magazine % 3 == 0 && _boss->magazine != 0)
	{
		_boss->fireIdleTime += dt;

		// 아직 쉬는 중이면 발사하지 않음
		if (_boss->fireIdleTime < fireIdleTimeMax)
			return;  // 쉬는 중

		// 쉬는 시간 끝나면 리셋하고 다음 발사 허용
		_boss->fireIdleTime = 0;
	}

	if (_boss->fireTime > _boss->fireDelay)
	{
		_boss->fireTime = 0;

		for (int i = 0; i < 4; i++)
		{
			if (CrossBullets_Boss[i][_boss->magazine].active == 0)
				CrossBullets_Boss[i][_boss->magazine].projPos = _boss->pos;

			CrossBullets_Boss[i][_boss->magazine].active = 1;
		}

		_boss->magazine++;

		if (_boss->magazine >= MAX_BULLETS_PER_ENEMY)
		{
			_boss->magazine = 0;
		}
	}
}

void CrossBulletFire(Boss* _boss)
{
	float dt = GetDt();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < MAX_BULLETS_PER_ENEMY; j++)
		{
			if (!CrossBullets_Boss[i][j].active)
			{
				CrossBullets_Boss[i][j].projPos = _boss->pos;
			}
			else
			{
				CrossBullets_Boss[i][j].projPos.x += CrossBullets_Boss[i][j].projSpd * CrossBullets_Boss[i][j].fireDir.x * dt;
				CrossBullets_Boss[i][j].projPos.y += CrossBullets_Boss[i][j].projSpd * CrossBullets_Boss[i][j].fireDir.y * dt;
			}
		}
	}
}

void Contact(Boss* _boss)
{
	float dt = GetDt();

	if (_boss->pos.x > 0.f)
	{
		_boss->pos.x -= dt * _boss->spd;
	}
	else
	{
		_boss->pos.x = 0;
	}
}

void RunAway(Boss* _boss)
{
	float dt = GetDt();

	float originSpd = _boss->spd;
	static int isLeft = 0;

	if (isLeft == 0)
	{
		_boss->spd -= dt * 1000;
		_boss->pos.x -= dt * _boss->spd;
		if (_boss->spd <= 0)
		{
			isLeft = 1;
			_boss->spd = 0;
		}
	}
	else if(_boss->pos.x < 3600.f)
	{
		_boss->spd += dt * 10000;
		_boss->pos.x += dt * _boss->spd;
		if (_boss->pos.x >= 3600.f)
		{
			_boss->spd = originSpd;
			return;
		}
	}
}

void BossLaserAttack(Boss* _boss)
{
	float dt = GetDt();

	_boss->idleTime += dt;
	_boss->waitTime += dt;

	float waitDuration = 1.f;

	if (_boss->laserCycle < 7)
	{
		if (_boss->waitTime > waitDuration)
		{

			if (_boss->idleTime >= _boss->timeArr[_boss->arrIndex])
			{
				do {
					_boss->rd = rand() % MAX_LASERS;
				} while (_boss->rd == _boss->rdprev);

				_boss->rdprev = _boss->rd;

				if (Lasers_BossStage[_boss->rd].active == 0)
				{
					Lasers_BossStage[_boss->rd].active = 1;
				}

				_boss->idleTime = 0.f;
				_boss->arrIndex++;

				if (_boss->arrIndex >= 5)
				{
					_boss->arrIndex = 0;
					_boss->laserCycle++;
				}
			}
		}
	}

	for (int i = 0; i < MAX_LASERS; i++)
	{
		if (Lasers_BossStage[i].active == 1)
		{
			CreateLaser(&BossLaserShooter[i], &Lasers_BossStage[i]);
			LaserAttack(&Lasers_BossStage[i]);
		}
	}

}

void InitPhaseThreeObstacle(Obstacle* _ob)
{
	for (int i = 0; i < 3; i++)
	{
		switch (i)
		{
		case 0:
			_ob[i].pos.x = 5000;
			_ob[i].pos.y = 0;
			break;
		case 1:
			_ob[i].pos.x = 6000;
			_ob[i].pos.y = 0;
			break;
		case 2:
			_ob[i].pos.x = 7000;
			_ob[i].pos.y = 0;
			break;
		}
		_ob[i].width = 300;
		_ob[i].height = 5000;
		_ob[i].sniper = 0;
	}
}

void PhaseThreeObstacle(Obstacle* _ob)
{
	
}

void BossStageController(Boss* _boss)
{
	float dt = GetDt();
	_boss->time += dt;
	if (_boss->time > 72.f)
	{
		_boss->state = DEAD;
	}
	else if (_boss->time > 50.f) _boss->phase = 4;
	else if (_boss->time > 35.f) _boss->phase = 3;
	else if (_boss->time > 15.5f) _boss->phase = 2;
	else if (_boss->time > 8.9f) _boss->phase = 1;
	else if (_boss->time < 8.f)	Contact(&boss);
	// 0페이즈: 보스 등장
	// 1페이즈: 보스 세발쏘는거
	// 2페이즈: 레이저 나오는거
	// 3페이즈: 이동
	if (_boss->phase == 1)
	{
		CrossBulletConditioner(_boss);
		CrossBulletFire(_boss);
	}
	if (_boss->phase == 2)
	{
		RunAway(_boss);
		BossLaserAttack(&boss);
	}
	if (_boss->phase == 3)
	{
		CameraMove(LD_LEFT, 40, 0.01f, 15);
	}

}