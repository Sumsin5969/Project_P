#pragma once
#include "../Player.h"
#include "../Enemy.h"
#include "../Obstacle.h"

void RenderWall(Obstacle*);
void RenderPlayer();
void RenderEnemy();
void RenderObstacle(Obstacle[][2]);
void LaserAttack();
void RenderBoss();
void RenderAll();
void StageTimer();
void CircleBulletFire(Enemy* e, Bullet* bullets);
void ChasingBulletFire(Enemy* e, Bullet* bullets);
void DirectBulletFire(Enemy* e, Bullet* bullets);