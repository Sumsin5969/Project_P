#pragma once
#include "cprocessing.h"
#include "Defines.h"
#include <stdlib.h>

typedef struct PlayerCharacter
{
	CP_Vector pos;
	float spd;
	int isDashing;
	float dashTimeMax;
	float dashTimer;
	float dashInvincibleTimeMax;	// 대쉬 후 약간의 무적타임을 주기 위함.

	float dashSpeedBoost;
	float originalSpd;
	float dashDecayRate;
	float size;
	CP_Vector direction;
	PlayerState playerState;
} PlayerCharacter;

void PlayerMove(void);
void ChangeSpeed(void);
void Dash(void);
void PlayerInit(void);
void DestroyPlayer();
void ChangePlayerSize();