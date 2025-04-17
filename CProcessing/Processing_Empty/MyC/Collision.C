#include <math.h>
#include <stdio.h>
#include "../Player.h"
#include "ZoomCamera.h"
#include "../Defines.h"
int isWall = 0;

int CheckWall()
{
	float rightwall = (GetCamera()->camZoom / 10) - (GetCamera()->camZoom / 10);
	if(player->pos.x + player->size >= rightwall)
	{
		//printf("player reached rightwall, camZoom: %f\n",GetCamera()->camZoom);
	}
	return isWall;
}