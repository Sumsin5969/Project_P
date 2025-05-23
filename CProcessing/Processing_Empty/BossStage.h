#pragma once
#include "cprocessing.h"
#include "MyC/PP_Renderer.h"
#include "MyC/ZoomCamera.h"
#include "Defines.h"
#include "stdio.h"
#include "MyC/GameManager.h"
#include <math.h>
#include "MyC/Collision.h"
#include "MyC/JhDebug.h"
#include "StageManager.h"
#include "Enemy.h"

void InitBossPhaseThree(Boss* _boss);

void InitPhaseThreeObstacle(Obstacle* _ob);

void BossStageController(Boss* _boss);
void BossBulletConditioner(Boss*, Bullet*);
void CrossBulletConditioner(Boss*);
void CrossBulletFire(Boss*);
void SpiralBulletConditioner(Boss* _boss);
void SpiralBulletFire(Boss* _boss);
void BossLaserAttack(Boss*);
void FirstLaserAttack(Boss*);
void Contact(Boss*);