#include "TutorialStage.h"

void InitTutorialObstacle(Obstacle* _ob)
{
	for (int i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0:
			_ob[i].pos.x = 0;
			_ob[i].pos.y = 250;
			_ob[i].width = 400;
			_ob[i].height = 50;
			_ob[i].type = WALL_TOP;
			break;
		case 1:
			_ob[i].pos.x = -225;
			_ob[i].pos.y = 400;
			_ob[i].width = 50;
			_ob[i].height = 350;
			_ob[i].type = WALL_LEFT;
			break;
		case 2:
			_ob[i].pos.x = 225;
			_ob[i].pos.y = 400;
			_ob[i].width = 50;
			_ob[i].height = 350;
			_ob[i].type = WALL_TOP;
			break;
		case 3:
			_ob[i].pos.x = 225;
			_ob[i].pos.y = 4000;
			_ob[i].width = 50;
			_ob[i].height = 350;
			_ob[i].type = WALL_BOTTOM;
			break;
		}
		_ob[i].sniper = 0;
	}
}

void InitStartBox(Obstacle* _ob)
{
	for (int i = 0;i < 2;i++)
	{
		switch (i)
		{
		case 0:
			_ob[i].pos.x = 0;
			_ob[i].pos.y = 375;
			_ob[i].width = 45;
			_ob[i].height = 45;
			break;
		case 1:
			_ob[i].pos.x = 0;
			_ob[i].pos.y = 375;
			_ob[i].width = 60;
			_ob[i].height = 60;
			break;
		}
	}
}