#pragma once
#include "../Player.h"
#include "../Enemy.h"
#include "../Obstacle.h"

void RenderWall(Obstacle*);
void RenderPlayer();
void RenderEnemy(Enemy* _enemy);
void RenderBullet(Bullet* _bullet);
void RenderObstacle(Obstacle* _obstacle);
void RenderPlayerShadow();

void RenderBoss();
void RenderAll();
void StageTimer();
