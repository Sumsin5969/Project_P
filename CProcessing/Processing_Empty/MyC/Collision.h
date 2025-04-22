#pragma once
#include "../Enemy.h"
typedef struct Obstacle Obstacle;
typedef struct Bullet Bullet;

void CheckWall(Obstacle*);
void CheckBullet(Enemy*);
void CheckWallBullet(Obstacle*, Bullet*);