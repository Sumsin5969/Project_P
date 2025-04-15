#include <math.h>
#include <stdio.h>
#include "../Player.h"
#include "ZoomCamera.h"
#include "../Defines.h"
int isWall = 0;

int CheckWall(PlayerCharacter pc)
{
	float rightwall = WIDTH - WALLWIDTHSIZE;
	if(pc.pos.x + pc.size >= rightwall)
	{
		printf("player reached rightwall, %f\n",GetCamera()->camZoom);
	}
	return isWall;
}