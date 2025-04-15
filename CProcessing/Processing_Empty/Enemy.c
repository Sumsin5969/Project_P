#include "Enemy.h"
#include "Defines.h"


void EnemyInit(Enemy* enemy)
{
	enemy->appTime = 10.f;
	enemy->isAttack = 0;
	enemy->spd = 100.f;
	enemy->pos.x = 0;
	enemy->pos.y = 0;
	enemy->size = 50.f;
}
