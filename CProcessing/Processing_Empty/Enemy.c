#include <stdlib.h>
#include <stdio.h>
#include "Enemy.h"
#include "Defines.h"
void EnemyInit()
{
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		enemies[i].appTime = 10.f;
		enemies[i].isAttack = 0;
		enemies[i].spd = 100.f;
		enemies[i].pos.x = CP_Random_RangeFloat(-850, 850);
		enemies[i].pos.y = CP_Random_RangeFloat(-400, -450);
		enemies[i].size = 30.f;
		enemies[i].active = 0;
		for (int j = 0; j < MAX_BULLETS_PER_ENEMY; j++)
		{
			allBullets[i][j].active = 0;
			allBullets[i][j].degree = j * (360.f / MAX_BULLETS_PER_ENEMY);
			allBullets[i][j].fireDelay = 2.f;
			allBullets[i][j].fireTime = 0.f;
			allBullets[i][j].projSpd = 1000.f;
			allBullets[i][j].projTime = 0.f;
			allBullets[i][j].size = 15.f;
		}
	}
}
void SetEnemyType(Enemy* enemy, StageState s_s, BulletType b_t, CP_Vector position, float bulletCooltime)
{
	
}
void DisableEnemy()
{
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		enemies[i].active = 0;
	}
}
