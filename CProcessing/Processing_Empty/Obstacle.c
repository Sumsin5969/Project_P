#include "Obstacle.h"
#include "Defines.h"

void InitWall(Obstacle* _wall, WallDirect _wd)
{
	switch (_wd)
	{
	case LEFT:
		_wall->pos = CP_Vector_Set(WALLWIDTHSIZE / 2, HEIGHT / 2);
		_wall->width = WALLWIDTHSIZE;
		_wall->height = HEIGHT;
		break;
	case RIGHT:
		_wall->pos = CP_Vector_Set(WIDTH - (WALLWIDTHSIZE / 2), HEIGHT / 2);
		_wall->width = WALLWIDTHSIZE;
		_wall->height = HEIGHT;
		break;
	case TOP:
		_wall->pos = CP_Vector_Set(WIDTH / 2, WALLHEIGHTSIZE / 2);
		_wall->width = WIDTH;
		_wall->height = WALLHEIGHTSIZE;
		break;
	case BOTTOM:
		_wall->pos = CP_Vector_Set(WIDTH / 2, HEIGHT - (WALLHEIGHTSIZE / 2));
		_wall->width = WIDTH;
		_wall->height = WALLHEIGHTSIZE;
		break;

	default:
		break;
	}
}