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

PlayerCharacter* GetPlayer();
void PlayerMove(void);
void ChangeSpeed(void);
void Dash(void);
void PlayerInit(void);