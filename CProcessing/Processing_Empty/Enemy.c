#include <stdlib.h>
#include <stdio.h>
#include "Enemy.h"
#include "Defines.h"
#include "MyC/GameManager.h"
#include "MyC/ZoomCamera.h"

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
			enemies[i].enemyPosition = TOPLEFT;
			break;
		case 1:
			enemies[i].pos.x = 850;
			enemies[i].pos.y = -450;
			enemies[i].enemyPosition = TOPRIGHT;
			break;
		case 2:
			enemies[i].pos.x = -850;
			enemies[i].pos.y = 450;
			enemies[i].enemyPosition = BOTTOMLEFT;
			break;
		case 3:
			enemies[i].pos.x = 850;
			enemies[i].pos.y = 450;
			enemies[i].enemyPosition = BOTTOMRIGHT;
			break;
		}

		for (int j = 0; j < MAX_BULLETS_PER_ENEMY; j++)
		{
			// Todo: 안쓰는 변수가 안생기도록 하는게 더 낫지만, 
			//       MJ 안쓰는 변수라도 초기화 하는 것을 권장
			PDBullets[i][j].projSpd = 1000.f;
			PDBullets[i][j].projTime = 0.f;
			PDBullets[i][j].fireTime = 0.f;
			PDBullets[i][j].fireDelay = 5.f;
			PDBullets[i][j].active = 0;
			PDBullets[i][j].size = 15.f;
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

// Enemy를 움직여주는 함수: 반시계 방향으로 Enemy를 지속적으로 이동

void EnemyMove(Enemy* enemy)
{
	float dt = GetDt() * (enemy->spd);
	if (enemy->enemyPosition == TOPLEFT)
	{
		enemy->pos.y += dt;
		// Zoom level 1에서 BOTTOMLEFT 적의 y좌표가 450이라서 거기까지 이동
		// 좌표에 zoom level을 곱해서 가변적인 좌표를 얻음
		if (enemy->pos.y >= 450)
		{
			enemy->enemyPosition = BOTTOMLEFT;
		}
	}
	if (enemy->enemyPosition == BOTTOMLEFT)
	{
		enemy->pos.x += dt * (17.f/9.f);
		if (enemy->pos.x >= 850)
		{
			enemy->enemyPosition = BOTTOMRIGHT;
		}
	}
	if (enemy->enemyPosition == BOTTOMRIGHT)
	{
		enemy->pos.y -= dt;
		if (enemy->pos.y <= -450)
		{
			enemy->enemyPosition = TOPRIGHT;
		}
	}
	if (enemy->enemyPosition == TOPRIGHT)
	{
		enemy->pos.x -= dt * (17.f / 9.f);
		if (enemy->pos.x <= -850)
		{
			enemy->enemyPosition = TOPLEFT;
		}
	}
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
