#include <stdio.h>
#include "cprocessing.h"
#include "Player.h"
#include "Defines.h"

#define UP CP_Input_KeyDown(KEY_UP)
#define DOWN CP_Input_KeyDown(KEY_DOWN)
#define LEFT CP_Input_KeyDown(KEY_LEFT)
#define RIGHT CP_Input_KeyDown(KEY_RIGHT)
PlayerState playerState;

void PlayerInit(void)
{
	player = (PlayerCharacter*)malloc(sizeof(PlayerCharacter));
	if (player == NULL)
	{
		printf("ERROR: player not initialized!\n");
		return;
	}
	player->isDashing = 0;
	player->dashTime = 0.3f;
	player->dashSpeedBoost = 1000.f;
	player->size = 50.f;
	player->pos.x = 0;
	player->pos.y = 0;
	player->spd = 400.f;
}

void PlayerMove(void) // 방향키를 입력받으면 플레이어를 이동시키는 함수
{
	if (player == NULL)
	{
		printf("ERROR: player not initialized!\n");
		return;
	}

	player->direction.x = 0;
	player->direction.y = 0;
	float dt = CP_System_GetDt();

	if (UP)    player->direction.y -= 1;
	if (DOWN)  player->direction.y += 1;
	if (LEFT)  player->direction.x -= 1;
	if (RIGHT) player->direction.x += 1;

	player->direction = CP_Vector_Normalize(player->direction);

	player->pos.x += player->direction.x * player->spd * dt;
	player->pos.y += player->direction.y * player->spd * dt;
}

void ChangeSpeed(void) // 디버깅용 속도 제어 함수
{
	if (CP_Input_KeyDown(KEY_1)) player->spd = 50;
	if (CP_Input_KeyDown(KEY_2)) player->spd = 100;
	if (CP_Input_KeyDown(KEY_3)) player->spd = 200;
	if (CP_Input_KeyDown(KEY_4)) player->spd = 300;
	if (CP_Input_KeyDown(KEY_5)) player->spd = 400;
	if (CP_Input_KeyDown(KEY_6)) player->spd = 500;
	if (CP_Input_KeyDown(KEY_7)) player->spd = 600;
	if (CP_Input_KeyDown(KEY_8)) player->spd = 700;
	if (CP_Input_KeyDown(KEY_9)) player->spd = 800;
	if (CP_Input_KeyDown(KEY_0)) player->spd = 900;
}

void Dash(void)
{
	float dt = CP_System_GetDt();

	if (CP_Input_KeyTriggered(KEY_LEFT_SHIFT) && !player->isDashing)
	{
		if (player->direction.x == 0 && player->direction.y == 0)
		{
			return;
		}
		player->isDashing = 1;
		player->dashTimer = player->dashTime;
		player->originalSpd = player->spd;
		player->spd += player->dashSpeedBoost;
		player->dashDecayRate = player->dashSpeedBoost / player->dashTimer;
	}

	if (player->isDashing)
	{
		player->dashTimer -= dt;
		player->spd -= player->dashDecayRate * dt;

		if (player->dashTimer <= 0.f)
		{
			player->spd = player->originalSpd;
			player->isDashing = 0;
		}
	}

}

void PlayerHit()
{
	playerState = HIT;
}

void DestroyPlayer()
{
	free(player);
	player = NULL;
}