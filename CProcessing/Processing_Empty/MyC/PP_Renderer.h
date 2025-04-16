#pragma once
#include "../Player.h"
#include "../Enemy.h"
#include "../Obstacle.h"

void RenderWall(Obstacle*);
void RenderPlayer(PlayerCharacter*);
void RenderEnemy(Enemy*);
//void RenderObstacle(Obstacle*);
void RenderBoss();

void RenderAll();
void EnemyLaserAttack();
