#pragma once
#include "../Player.h"
#include "../Enemy.h"
#include "../Obstacle.h"

void RenderWall(Obstacle*);
void RenderPlayer();
void RenderEnemy(Enemy* _enemy);
void RenderBullet(Bullet* _bullet);
void RenderLaser(Enemy*, Laser*);
void RenderObstacle(Obstacle* _obstacle);

void RenderBoss();
void RenderAll();
void StageTimer();

