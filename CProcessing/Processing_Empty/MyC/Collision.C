#include <math.h>
#include <stdio.h>
#include "../Player.h"
#include "ZoomCamera.h"
#include "../Defines.h"
#include "../Obstacle.h"

int isWall = 0;

PlayerState CheckWall(Obstacle* _obstacle)
{
	CP_Vector camPos = GetCamera()->camPos;

	for (int i = 0; i < 4; ++i)
	{
		switch (_obstacle[i].type)
		{
		case WALL_LEFT:
			if (player->pos.x - player->size / 2 + camPos.x < _obstacle[i].pos.x + _obstacle[i].width / 2)
			{
				printf("왼쪽벽에 부딪힘");
				return HIT;
			}
			break;
		case WALL_RIGHT:
			if (_obstacle[i].pos.x - _obstacle[i].width / 2 < player->pos.x + player->size / 2 + camPos.x)
			{
				printf("오른쪽벽에 부딪힘\n");
				return HIT;
			}
			break;
		case WALL_TOP:
			if (player->pos.y - player->size / 2 + camPos.y < _obstacle[i].pos.y + _obstacle[i].height / 2)
			{
				printf("위쪽벽에 부딪힘\n");
				return HIT;
			}
			break;
		case WALL_BOTTOM:
			if (_obstacle[i].pos.y - _obstacle[i].height / 2 < player->pos.y + player->size / 2 + camPos.y)
			{
				printf("아래벽에 부딪힘\n");
				return HIT;
			}
			break;
		}

	}

	return NORMAL;
}