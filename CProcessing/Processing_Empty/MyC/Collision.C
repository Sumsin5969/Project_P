#include <math.h>
#include <stdio.h>
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
	float distanceSquared;
	float radiusSum;

	dx = player->pos.x - _bullet->projPos.x;
	dy = player->pos.y - _bullet->projPos.y;

	distanceSquared = dx * dx + dy * dy;
	radiusSum = player->size + _bullet->size;
	if (distanceSquared <= (radiusSum * radiusSum))
	{
		player->playerState = HIT;
		printf("플레이어 쳐맞음");
	}
}

void CheckLaser()
{

}

void CheckWall(Obstacle* _obstacle)
{
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
				printf("왼쪽벽에 부딪힘\n");
				player->playerState = HIT;
			}
			break;
		case WALL_RIGHT:
			if (wallRight < playerRight)
			{
				printf("오른쪽벽에 부딪힘\n");
				player->playerState = HIT;
			}
			break;
		case WALL_TOP:
			if (playerTop < wallTop)
			{
				printf("위쪽벽에 부딪힘\n");
				player->playerState = HIT;
			}
			break;
		case WALL_BOTTOM:
			if (wallBottom < playerBottom)
			{
				printf("아래벽에 부딪힘\n");
				player->playerState = HIT;

			}
			break;
		}

	}
}

void CheckWallBullet(Obstacle* _obstacle, Bullet* b)
{
	CP_Vector camPos = GetCamera()->camPos;
	float camZoom = GetCamera()->camZoom;


	float bulletHalfSize;
	float bulletLeft;
	float bulletRight;
	float bulletTop;
	float bulletBottom;

	for (int i = 0; i < MAX_BULLETS_PER_ENEMY; i++)
	{
		bulletHalfSize = b[i].size / 2;
		bulletLeft = (b[i].projPos.x - bulletHalfSize) * camZoom + camPos.x;
		bulletRight = (b[i].projPos.x + bulletHalfSize) * camZoom + camPos.x;
		bulletTop = (b[i].projPos.y - bulletHalfSize) * camZoom + camPos.y;
		bulletBottom = (b[i].projPos.y + bulletHalfSize) * camZoom + camPos.y;
	}
	float wallLeft = _obstacle[WALL_LEFT].pos.x + _obstacle[WALL_LEFT].width / 2;
	float wallRight = _obstacle[WALL_RIGHT].pos.x - _obstacle[WALL_RIGHT].width / 2;
	float wallTop = _obstacle[WALL_TOP].pos.y + _obstacle[WALL_TOP].height / 2;
	float wallBottom = _obstacle[WALL_BOTTOM].pos.y - _obstacle[WALL_BOTTOM].height / 2;

	for (int i = 0; i < 4; ++i)
	{
		switch (_obstacle[i].type)
		{
		case WALL_LEFT:
			if (bulletLeft < wallLeft)
			{
				printf("왼쪽벽에 부딪힘\n");
				b[i].active = 0;
			}
			break;
		case WALL_RIGHT:
			if (wallRight < bulletRight)
			{
				printf("오른쪽벽에 부딪힘\n");
				b[i].active = 0;
			}
			break;
		case WALL_TOP:
			if (bulletTop < wallTop)
			{
				printf("위쪽벽에 부딪힘\n");
				b[i].active = 0;
			}
			break;
		case WALL_BOTTOM:
			if (wallBottom < bulletBottom)
			{
				printf("아래벽에 부딪힘\n");
				b[i].active = 0;

			}
			break;
		}

	}
}