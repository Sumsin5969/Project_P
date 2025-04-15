#include "Enemy.h"
#include "Defines.h"

int LaserAlpha = 100;
int LaserAlphaMax = 220;
float LaserChargeTime = 2.f;
float LaserTimer = 0.f;
float LaserAttackTimer = 0.f;
float LaserTime = 3.f;

void EnemyInit(Enemy* enemy)
{
	enemy->appTime = 10.f;
	enemy->isAttack = 0;
	enemy->spd = 100.f;
	enemy->pos.x = 0;
	enemy->pos.y = 0;
	enemy->size = 50.f;
}
void EnemyAttack()
{
	float dt = CP_System_GetDt();
	if (LaserTimer < LaserChargeTime)
	{
		LaserTimer += dt;
		LaserAlpha = (int)(LaserTimer / LaserChargeTime * LaserAlphaMax);
		if (LaserAlpha > LaserAlphaMax) LaserAlpha = LaserAlphaMax;
		CP_Settings_Fill(CP_Color_Create(200, 100, 100, LaserAlpha));
		CP_Graphics_DrawRect(WIDTH / 2, 100, 100, HEIGHT-300); // 레이저 위치
	}
	else
	{
		LaserAttackTimer += dt;
		if (LaserAttackTimer <= LaserTime)
		{
			CP_Settings_Fill(CP_Color_Create(238, 1, 147, 255));
		}
	}
}