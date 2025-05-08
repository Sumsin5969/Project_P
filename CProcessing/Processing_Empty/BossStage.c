#include "cprocessing.h"
#include "MyC/PP_Renderer.h"
#include "MyC/ZoomCamera.h"
#include "Defines.h"
#include "stdio.h"
#include "MyC/GameManager.h"
#include <math.h>
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

void BossStageController(Boss* _boss)
{
	float dt = GetDt();

	_boss->time += dt;
	if (_boss->time > 100.f)
	{
		_boss->state = DEAD;
	}
	else if (_boss->time > 80.f)
	{

	}
	else if (_boss->time > 60.f)
	{

	}
	else if (_boss->time > 18.f) _boss->phase = 2;
	else if (_boss->time > 8.9f) _boss->phase = 1;
	else if (_boss->time < 8.f)	Contact(&boss);

	if (_boss->phase == 1)
	{
		CrossBulletConditioner(_boss);
		CrossBulletFire(_boss);
	}

}