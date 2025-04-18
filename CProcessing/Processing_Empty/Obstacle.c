#include "Obstacle.h"
#include "Defines.h"

void InitWall(Obstacle* _wall)
{

	switch (_wall->type)
	{
	case WALL_LEFT:
		_wall->pos = CP_Vector_Set(WALLWIDTHSIZE / 2, HEIGHT / 2);
		_wall->width = WALLWIDTHSIZE;
		_wall->height = HEIGHT;
		break;
	case WALL_RIGHT:
		_wall->pos = CP_Vector_Set(WIDTH - (WALLWIDTHSIZE / 2), HEIGHT / 2);
		_wall->width = WALLWIDTHSIZE;
		_wall->height = HEIGHT;
		break;
	case WALL_TOP:
		_wall->pos = CP_Vector_Set(WIDTH / 2, WALLHEIGHTSIZE / 2);
		_wall->width = WIDTH;
		_wall->height = WALLHEIGHTSIZE;
		break;
	case WALL_BOTTOM:
		_wall->pos = CP_Vector_Set(WIDTH / 2, HEIGHT - (WALLHEIGHTSIZE / 2));
		_wall->width = WIDTH;
		_wall->height = WALLHEIGHTSIZE;
		break;

	default:
		break;
	}
}