#include <stdlib.h>
#include <stdio.h>
#include "Enemy.h"
#include "Defines.h"
void EnemyInit()
{
	enemy = (Enemy*)calloc(1, sizeof(Enemy));
	if (enemy == NULL)
	{
		printf("ERROR: enemy not initialized!\n");
		return;
	}
	enemy->appTime = 10.f;
	enemy->isAttack = 0;
	enemy->spd = 100.f;
	enemy->pos.x = 0;
	enemy->pos.y = 0;
	enemy->size = 50.f;
}
void BulletInit()
{
	for (int i = 0; i < MAX_BULLET; i++)
	{
		bullets[i].active = 0;
		bullets[i].degree = i * (360.f / MAX_BULLET);
		bullets[i].fireCoolTime = .5f;
		bullets[i].fireTime = 0.f;
		bullets[i].projSpd = 200.f;
		bullets[i].size = 10.f;
	}
}
void DestroyEnemy()
{
	free(enemy);
	enemy = NULL;
}
