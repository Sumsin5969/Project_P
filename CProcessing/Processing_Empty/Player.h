#pragma once
#include "cprocessing.h"
#include "Defines.h"
#include <stdlib.h>

typedef struct PlayerCharacter
{
	CP_Vector pos;
	float spd;
	int isDashing;
	int isHit;
	float dashTime;
	float dashTimer;
	float dashSpeedBoost;
	float originalSpd;
	float dashDecayRate;
	float size;
	CP_Vector direction;
	PlayerState playerState;
} PlayerCharacter;

PlayerCharacter* player;

void PlayerMove(void);
void ChangeSpeed(void);
void Dash(void);
void PlayerInit(void);
void DestroyPlayer();