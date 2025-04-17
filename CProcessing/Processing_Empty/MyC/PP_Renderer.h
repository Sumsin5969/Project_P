#pragma once
#include "../Player.h"
#include "../Enemy.h"
#include "../Obstacle.h"

void RenderWall(Obstacle*);
void RenderPlayer();
void RenderEnemy();
//void RenderObstacle(Obstacle*);
void EnemyLaserAttack();
void EnemyBulletFire();
void RenderBoss();
void RenderAll();
