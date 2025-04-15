#pragma once
#include "cprocessing.h"
#include "Defines.h"

typedef struct Obstacle
{
	CP_Vector pos;
	float width;
	float height;
} Obstacle;

void InitWall(Obstacle _wall, WallDirect _wd);
