#include "Obstacle.h"
#include "Defines.h"

void SetWallType(Obstacle* _wall)
{
	for (int i = 0; i < 4; ++i)
	{
		_wall[i].type = (ObstacleType)i;
	}
}

void InitWall(Obstacle* _wall)
{
	for (int i = 0; i < 4; ++i)
	{
		switch (_wall[i].type)
		{
		case WALL_LEFT:
			_wall[i].pos = CP_Vector_Set(WALLWIDTHSIZE / 2, HEIGHT / 2);
			_wall[i].width = WALLWIDTHSIZE;
			_wall[i].height = HEIGHT;
			break;
		case WALL_RIGHT:
			_wall[i].pos = CP_Vector_Set(WIDTH - (WALLWIDTHSIZE / 2), HEIGHT / 2);
			_wall[i].width = WALLWIDTHSIZE;
			_wall[i].height = HEIGHT;
			break;
		case WALL_TOP:
			_wall[i].pos = CP_Vector_Set(WIDTH / 2, WALLHEIGHTSIZE / 2);
			_wall[i].width = WIDTH;
			_wall[i].height = WALLHEIGHTSIZE;
			break;
		case WALL_BOTTOM:
			_wall[i].pos = CP_Vector_Set(WIDTH / 2, HEIGHT - (WALLHEIGHTSIZE / 2));
			_wall[i].width = WIDTH;
			_wall[i].height = WALLHEIGHTSIZE;
			break;

		default:
			break;
		}
	}
}