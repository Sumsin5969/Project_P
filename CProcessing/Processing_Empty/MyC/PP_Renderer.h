#pragma once
#include "../Player.h"
#include "../Enemy.h"
#include "../Obstacle.h"

void RenderWall(Obstacle*);
void RenderPlayer();
void RenderEnemy(Enemy* _enemy);
void RenderBullet(Bullet* _bullet);
void RenderLaser(Laser*);
void RenderObstacle(Obstacle* _obstacle);

void RenderPlayerShadow();


void RenderEnemy_StageOne();
void RenderBullet_StageOne();
void RenderEnemy_StageTwo();
void RenderLaser_StageTwo();
void RenderEnemy_StageThree();
void RenderBullet_StageThree();

void RenderEnemyAll();
void RenderAttackAll();

void RenderBoss(Boss*);

void RenderAll();
void StageTimer();