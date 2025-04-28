#pragma once
#include "../Enemy.h"
typedef struct Obstacle Obstacle;
typedef struct Bullet Bullet;

void CheckWallBullet(Obstacle*, Bullet*);
void CheckWall(Obstacle* );
void CheckBullet(Bullet* );
void CheckObstacle(Obstacle* _obstacle);
void CheckLaser(Laser* _laser);
void CheckEnemy(Enemy*);
void CheckBoss(Boss*);
