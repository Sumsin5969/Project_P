#include "Obstacle.h"
#include "Defines.h"

void SetWallType(Obstacle* _wall)
{
	for (int i = 0; i < 4; ++i)
	{
		_wall[i].type = (ObstacleType)i;
	}
}

void InitObstacle(Obstacle _obstacle[7][2])
{
	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			_obstacle[i][j].pos = CP_Vector_Set(10000, 10000);
			_obstacle[i][j].width = 100;
			_obstacle[i][j].height = 100;
		}
	}

	_obstacle[0][0].pos = CP_Vector_Set(200, 500);
	_obstacle[0][1].pos = CP_Vector_Set(500, 200);
	_obstacle[1][0].pos = CP_Vector_Set(700, 800);
	_obstacle[1][1].pos = CP_Vector_Set(1000, 400);
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