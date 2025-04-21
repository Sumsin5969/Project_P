#include <stdlib.h>
#include <stdio.h>
#include "Enemy.h"
#include "Defines.h"
// 적과 탄환 초기화
// 
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
		// Todo: 안쓰는 변수가 안생기도록 하는게 더 낫지만, 
		//       MJ 안쓰는 변수라도 초기화 하는 것을 권장
		PDBullets[i].projSpd = 1000.f;
		PDBullets[i].projTime = 0.f;
		PDBullets[i].fireTime = 0.f;
		PDBullets[i].fireDelay = 5.f;
		PDBullets[i].active = 0;
		PDBullets[i].size = 15.f;

		for (int j = 0; j < MAX_BULLETS_PER_ENEMY; j++)
		{
			CircleBullets[i][j].projSpd = 500.f;
			CircleBullets[i][j].projTime = 0.f;
			CircleBullets[i][j].fireTime = 0.f;
			CircleBullets[i][j].fireDelay = 5.f;
			CircleBullets[i][j].degree = j * (360.f / MAX_BULLETS_PER_ENEMY);
			CircleBullets[i][j].active = 0;
			CircleBullets[i][j].size = 15.f;
		}
	}
}
void EnemyMove(Enemy enemy)
{

}
void LaserInit()
{

}

void DisableEnemy()
{
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		enemies[i].active = 0;
	}
}
