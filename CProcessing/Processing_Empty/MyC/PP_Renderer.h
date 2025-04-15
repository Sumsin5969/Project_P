#pragma once
#include "../Player.h"
#include "../Enemy.h"

void RenderWall();
void RenderPlayer(PlayerCharacter*);
void RenderEnemy(Enemy*);
//void RenderObstacle(Obstacle*);
void RenderBoss();

void RenderAll();
void EnemyLaserAttack();
