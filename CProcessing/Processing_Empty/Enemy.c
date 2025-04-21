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
		enemies[i].size = 50.f;
		enemies[i].active = 0;
		switch (i)
		{
		case 0:
			enemies[i].pos.x = -850;
			enemies[i].pos.y = -450;
			break;
		case 1:
			enemies[i].pos.x = 850;
			enemies[i].pos.y = -450;
			break;
		case 2:
			enemies[i].pos.x = -850;
			enemies[i].pos.y = 450;
			break;
		case 3:
			enemies[i].pos.x = 850;
			enemies[i].pos.y = 450;
			break;
		}
		for (int j = 0; j < MAX_BULLETS_PER_ENEMY; j++)
		{
			allBullets[i][j].active = 0;
			allBullets[i][j].degree = j * (360.f / MAX_BULLETS_PER_ENEMY);
			allBullets[i][j].fireDelay = 5.f;
			allBullets[i][j].fireTime = 0.f;
			allBullets[i][j].projSpd = 500.f;
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
