#pragma once
#include "cprocessing.h"
#include "Defines.h"

typedef struct Obstacle
{
	CP_Vector pos;
	float width;
	float height;
	ObstacleType type;
	int sniper;
} Obstacle;

void InitWall(Obstacle* _wall);
void SetWallType(Obstacle*);
void InitObstacle(Obstacle[7][2]);
