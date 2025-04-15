#pragma once
#include "cprocessing.h"

typedef struct PlayerCharacter
{
    CP_Vector pos;
    float spd;
	int isDashing;
	float dashTime;
	float dashTimer;
	float dashSpeedBoost;
	float originalSpd;
	float dashDecayRate;
	float size;
	CP_Vector direction;
} PlayerCharacter;

typedef struct Enemy
{
	CP_Vector pos;
	float spd;
	int isAttack;
	float appTime;
	float size;
} Enemy;

typedef struct Obstacle
{
	CP_Vector pos;
	float width;
	float height;
} Obstacle;

typedef struct BossCharacter
{
	CP_Vector pos;
	float size;
	// 보스에 추가될 요소들


} BossCharacter;


void PlayerMove(void);
void InitChar(float, float);
void ChangeSpeed(void);
void Dash(void);
void PlayerInit(void);
void DrawWall(void);
PlayerCharacter* GetPlayer();
