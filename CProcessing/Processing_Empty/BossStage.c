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
	_boss->fireTime += dt;
	if (_boss->fireTime > _boss->fireDelay)
	{
		_boss->fireTime = 0;
		for (int i = 0; i < 4; i++)
		{
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
	if (_boss->pos.x >= 0.f)
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

	static float bossStageTimer = 0.f;
	bossStageTimer += dt;

	const float warningTimeMax = 3.f;
	if (bossStageTimer > 100.f)
	{
		_boss->state = DEAD;
	}
	else if (bossStageTimer > 80.f)
	{

	}
	else if (bossStageTimer > 60.f)
	{

	}
	else if (bossStageTimer > 40.f)
	{

	}
	else if (bossStageTimer > 20.f)
	{

	}
	else if (bossStageTimer > 16.f)
	{
		Contact(&boss);
	}


	if (_boss->phase == 0)
	{
		_boss->state = BOSSWARNING;
	}

	if (_boss->state == BOSSWARNING)
	{
		if (_boss->time <= warningTimeMax)
		{
			_boss->time += dt;
		}
		else
		{
			_boss->time = 0.f;
			_boss->state = APPEAR;
			_boss->active = 1;
		}
	}
	if (_boss->phase == 1)
	{
		//CrossBulletFire(_boss);
	}

}