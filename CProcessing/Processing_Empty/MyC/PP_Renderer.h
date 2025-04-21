#pragma once
#include "../Player.h"
#include "../Enemy.h"
#include "../Obstacle.h"

void RenderWall(Obstacle*);
void RenderPlayer();
void RenderEnemy(Enemy* _enemy);
void RenderBullet(Bullet* _bullet);
void RenderObstacle(Obstacle* _obstacle);

void LaserAttack();
void CircleBulletFire(Enemy* e, Bullet* bullets);
void RenderBoss();
void RenderAll();
void StageTimer();
void ChasingBulletFire(Enemy* e, Bullet* b);
void DirectBulletFire(Enemy* e, Bullet* b);