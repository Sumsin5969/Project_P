#include <math.h>
#include <stdio.h>
#include "../Player.h"
#include "ZoomCamera.h"
#include "../Defines.h"
#include "../Obstacle.h"

int isWall = 0;

PlayerState CheckWall(Obstacle* _obstacle)
{
	//CP_Vector camPos = GetCamera()->camPos;

	switch (_obstacle->type)
	{
	case WALL_LEFT:
		
		if (player->pos.x - player->size < _obstacle->width)
		{
			printf("왼쪽벽 X = %f", player->pos.x - player->size);
			printf("왼쪽벽에 부딪힘\n");
			return HIT;
		}
		break;
	case WALL_RIGHT:
		if (_obstacle->pos.x - _obstacle->width < player->pos.x + player->size);
		{
			printf("오른쪽벽에 부딪힘\n");
			return HIT;
		}
		break;
	case WALL_TOP:
		if (-_obstacle->height < player->pos.y - player->size);
		{
			printf("위쪽벽에 부딪힘\n");
			return HIT;
		}
		break;
	case WALL_BOTTOM:
		if (player->pos.y - player->size < _obstacle->pos.y + _obstacle->height);
		{
			printf("아래벽에 부딪힘\n");
			return HIT;
		}
		break;
	}
	
	return NORMAL;
}