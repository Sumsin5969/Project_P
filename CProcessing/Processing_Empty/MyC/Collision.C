#include <math.h>
#include <stdio.h>
#include <math.h>
#include "GameManager.h"
#include "ZoomCamera.h"
#include "../Defines.h"
#include "../Obstacle.h"
#include "../Enemy.h"

int isWall = 0;

void CheckBullet(Bullet* _bullet)
{

	float dx;	// 델타 x
	float dy;	// 델타 y
	float distance;
	float radiusSum;
	for (int i = 0; i < MAX_BULLETS_PER_ENEMY; i++)
	{
		if (!_bullet[i].active) continue;
		dx = player->pos.x - _bullet[i].projPos.x;
		dy = player->pos.y - _bullet[i].projPos.y;
		distance = sqrtf(dx * dx + dy * dy);

		radiusSum = player->size / 2.f + _bullet[i].size / 2.f;

		if (distance <= radiusSum)
		{
			if (player->playerState == NORMAL)
			{
				_bullet[i].sniper = 1;
				player->playerState = HIT;
			}
		}
	}
}

void CheckObstacle(Obstacle* _obstacle) // AABB - Circle collision
{
	float radius = player->size / 2;

	// 1. 원 중심 계산 (좌상단 기준으로 반지름 보정)
	CP_Vector circleCenter = CP_Vector_Set(player->pos.x, player->pos.y);

	// 2. 박스 AABB 좌표
	float boxLeft = _obstacle->pos.x - _obstacle->width / 2;
	float boxRight = _obstacle->pos.x + _obstacle->width / 2;
	float boxTop = _obstacle->pos.y - _obstacle->height / 2;
	float boxBottom = _obstacle->pos.y + _obstacle->height / 2;

	// 3. 가장 가까운 박스 안 점 계산 (클램핑)
	float closestX = CP_Math_ClampFloat(circleCenter.x, boxLeft, boxRight);
	float closestY = CP_Math_ClampFloat(circleCenter.y, boxTop, boxBottom);

	// 4. 거리 계산 (원 중심 → 가장 가까운 점)
	float dx = circleCenter.x - closestX;
	float dy = circleCenter.y - closestY;
	float distanceSq = dx * dx + dy * dy;
	float radiusSq = radius * radius;

	// 5. 충돌 여부 판단
	if (distanceSq < radiusSq)
	{
		if (player->playerState == NORMAL)
		{
			_obstacle->sniper = 1;

			player->playerState = HIT;
		}
	}
}

void CheckLaser(Laser* _laser)
{
	if (_laser->state != ATTACK) return;

	float radius = player->size / 2;

	// 1. 원 중심 계산 (좌상단 기준으로 반지름 보정)
	CP_Vector circleCenter = CP_Vector_Set(player->pos.x, player->pos.y);

	// 2. 박스 AABB 좌표
	float boxLeft = _laser->pos.x - _laser->laserWidth / 2;
	float boxRight = _laser->pos.x + _laser->laserWidth / 2;
	float boxTop = _laser->pos.y - _laser->laserHeight / 2;
	float boxBottom = _laser->pos.y + _laser->laserHeight / 2;

	// 3. 가장 가까운 박스 안 점 계산 (클램핑)
	float closestX = CP_Math_ClampFloat(circleCenter.x, boxLeft, boxRight);
	float closestY = CP_Math_ClampFloat(circleCenter.y, boxTop, boxBottom);

	// 4. 거리 계산 (원 중심 → 가장 가까운 점)
	float dx = circleCenter.x - closestX;
	float dy = circleCenter.y - closestY;
	float distanceSq = dx * dx + dy * dy;
	float radiusSq = radius * radius;

	// 5. 충돌 여부 판단
	if (distanceSq < radiusSq)
	{
		if (player->playerState == NORMAL)
		{
			_laser->sniper = 1;

			player->playerState = HIT;
		}
	}
}

void CheckWall(Obstacle* _obstacle)
{
	if (player->playerState != NORMAL) return;

	CP_Vector camPos = GetCamera()->camPos;
	float camZoom = GetCamera()->camZoom;

	float playerHalfSize = player->size / 2;

	float playerLeft = (player->pos.x - playerHalfSize) * camZoom + camPos.x;
	float playerRight = (player->pos.x + playerHalfSize) * camZoom + camPos.x;
	float playerTop = (player->pos.y - playerHalfSize) * camZoom + camPos.y;
	float playerBottom = (player->pos.y + playerHalfSize) * camZoom + camPos.y;

	float wallLeft = _obstacle[WALL_LEFT].pos.x + _obstacle[WALL_LEFT].width / 2;
	float wallRight = _obstacle[WALL_RIGHT].pos.x - _obstacle[WALL_RIGHT].width / 2;
	float wallTop = _obstacle[WALL_TOP].pos.y + _obstacle[WALL_TOP].height / 2;
	float wallBottom = _obstacle[WALL_BOTTOM].pos.y - _obstacle[WALL_BOTTOM].height / 2;

	for (int i = 0; i < 4; ++i)
	{
		switch (_obstacle[i].type)
		{
		case WALL_LEFT:
			if (playerLeft < wallLeft)
			{
				if (player->playerState == NORMAL)
				{
					_obstacle->sniper = 1;

					player->playerState = HIT;
				}
			}
			break;
		case WALL_RIGHT:
			if (wallRight < playerRight)
			{
				if (player->playerState == NORMAL)
				{
					_obstacle->sniper = 1;
					player->playerState = HIT;
				}
			}
			break;
		case WALL_TOP:
			if (playerTop < wallTop)
			{
				if (player->playerState == NORMAL)
				{
					_obstacle->sniper = 1;
					player->playerState = HIT;
				}
			}
			break;
		case WALL_BOTTOM:
			if (wallBottom < playerBottom)
			{
				if (player->playerState == NORMAL)
				{
					_obstacle->sniper = 1;
					player->playerState = HIT;
				}
			}
			break;
		}
	}
}
static int bulletCount = 0;

void CheckWallBullet(Obstacle* _obstacle, Bullet* b)
{
	CP_Vector camPos = GetCamera()->camPos;
	float camZoom = GetCamera()->camZoom;

	for (int j = 0; j < MAX; j++)
	{
		for (int i = 0; i < MAX_BULLETS_PER_ENEMY; i++)
		{
			float bulletHalfSize = b[i].size / 2;
			float bulletLeft = (b[i].projPos.x + bulletHalfSize) * camZoom + camPos.x;
			float bulletRight = (b[i].projPos.x - bulletHalfSize) * camZoom + camPos.x;
			float bulletTop = (b[i].projPos.y + bulletHalfSize) * camZoom + camPos.y;
			float bulletBottom = (b[i].projPos.y - bulletHalfSize) * camZoom + camPos.y;

			float wallLeft = _obstacle[WALL_LEFT].pos.x + _obstacle[WALL_LEFT].width / 2;
			float wallRight = _obstacle[WALL_RIGHT].pos.x - _obstacle[WALL_RIGHT].width / 2;
			float wallTop = _obstacle[WALL_TOP].pos.y + _obstacle[WALL_TOP].height / 2;
			float wallBottom = _obstacle[WALL_BOTTOM].pos.y - _obstacle[WALL_BOTTOM].height / 2;

			/*if (b[i].active == 0)
			{
				printf("%d 번째 총알은 비활성화다\n", i);
				continue;
			}*/

			switch (_obstacle[j].type)
			{
			case WALL_LEFT:
				if (bulletLeft < wallLeft)
				{
					b[i].active = 0;
					//printf("총알회수 %d 번째 총알\n", bulletCount++);
				}
				break;
			case WALL_RIGHT:
				if (wallRight < bulletRight)
				{
					b[i].active = 0;
					//printf("총알회수 %d 번째 총알\n", bulletCount++);
				}
				break;
			case WALL_TOP:
				if (bulletTop < wallTop)
				{
					b[i].active = 0;
					//printf("총알회수 %d 번째 총알\n", bulletCount++);
				}
				break;
			case WALL_BOTTOM:
				if (wallBottom < bulletBottom)
				{
					b[i].active = 0;
					//printf("총알회수 %d 번째 총알\n", bulletCount++);
				}
				break;
			}
		}
	}
}

void CheckEnemy(Enemy* _enemy) // AABB - Circle collision
{
	float radius = player->size / 2;

	// 1. 원 중심 계산 (좌상단 기준으로 반지름 보정)
	CP_Vector circleCenter = CP_Vector_Set(player->pos.x, player->pos.y);

	// 2. 박스 AABB 좌표
	float _enemyLeft = _enemy->pos.x - _enemy->size / 2;
	float _enemyRight = _enemy->pos.x + _enemy->size / 2;
	float _enemyTop = _enemy->pos.y - _enemy->size / 2;
	float _enemyBottom = _enemy->pos.y + _enemy->size / 2;

	// 3. 가장 가까운 박스 안 점 계산 (클램핑)
	float closestX = CP_Math_ClampFloat(circleCenter.x, _enemyLeft, _enemyRight);
	float closestY = CP_Math_ClampFloat(circleCenter.y, _enemyTop, _enemyBottom);

	// 4. 거리 계산 (원 중심 → 가장 가까운 점)
	float dx = circleCenter.x - closestX;
	float dy = circleCenter.y - closestY;
	float distanceSq = dx * dx + dy * dy;
	float radiusSq = radius * radius;

	// 5. 충돌 여부 판단
	if (distanceSq < radiusSq)
	{
		if (player->playerState == NORMAL)
		{
			_enemy->sniper = 1;

			player->playerState = HIT;
		}
	}
}

void CheckBoss(Boss* _boss) // AABB - Circle collision
{
	float radius = player->size / 2;

	// 1. 원 중심 계산 (좌상단 기준으로 반지름 보정)
	CP_Vector circleCenter = CP_Vector_Set(player->pos.x, player->pos.y);

	// 2. 박스 AABB 좌표
	float _bossLeft = _boss->pos.x - _boss->size / 2;
	float _bossRight = _boss->pos.x + _boss->size / 2;
	float _bossTop = _boss->pos.y - _boss->size / 2;
	float _bossBottom = _boss->pos.y + _boss->size / 2;

	// 3. 가장 가까운 박스 안 점 계산 (클램핑)
	float closestX = CP_Math_ClampFloat(circleCenter.x, _bossLeft, _bossRight);
	float closestY = CP_Math_ClampFloat(circleCenter.y, _bossTop, _bossBottom);

	// 4. 거리 계산 (원 중심 → 가장 가까운 점)
	float dx = circleCenter.x - closestX;
	float dy = circleCenter.y - closestY;
	float distanceSq = dx * dx + dy * dy;
	float radiusSq = radius * radius;

	// 5. 충돌 여부 판단
	if (distanceSq < radiusSq)
	{
		if (player->playerState == NORMAL)
		{
			_boss->sniper = 1;

			player->playerState = HIT;
		}
	}
}