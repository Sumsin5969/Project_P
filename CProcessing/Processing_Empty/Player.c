#include <stdio.h>
#include "cprocessing.h"
//#include "Player.h"
#include "MyC/GameManager.h"
#include "Defines.h"
#include "SoundManager.h"

#define UP CP_Input_KeyDown(KEY_UP)
#define DOWN CP_Input_KeyDown(KEY_DOWN)
#define LEFT CP_Input_KeyDown(KEY_LEFT)
#define RIGHT CP_Input_KeyDown(KEY_RIGHT)

float playerOriSize = 50.f;
int playerSizeState = 0; // -1 작아짐 / 0 기본 / 1 커짐 
float sizingSpeed = 50.f;

void PlayerInit(void)
{
	player = (PlayerCharacter*)malloc(sizeof(PlayerCharacter));
	if (player == NULL)
	{
		printf("ERROR: player not initialized!\n");
		return;
	}
	player->isDashing = 0;
	player->playerState = NORMAL;
	player->dashTimeMax = .3f;
	player->dashSpeedBoost = 1000.f;
	player->size = 50.f;
	player->pos.x = 0;
	player->pos.y = 0;
	player->spd = 400.f;
	player->dashInvincibleTimeMax = player->dashTimeMax + 0.05f; // 대쉬끝나고 n 초 무적시간 더주기위해
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
	float dt = GetDt();

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
	float dt = GetDt();

	if (CP_Input_KeyTriggered(KEY_LEFT_SHIFT) && !player->isDashing)
	{
		if (player->direction.x == 0 && player->direction.y == 0) // 나중에 수정해야함 (방향키없을때 대쉬안됌)
		{
			return;
		}

		player->isDashing = 1;
		player->dashTimer = player->dashTimeMax;
		player->originalSpd = player->spd;
		player->spd += player->dashSpeedBoost;
		player->dashDecayRate = player->dashSpeedBoost / player->dashTimer;

		player->playerState = INVINCIBLE;
	}

	if (player->isDashing)
	{
		player->dashTimer -= dt;
		player->spd -= player->dashDecayRate * dt;

		static float saveTimer = 0.0f;	// 잔상용
		saveTimer += dt;

		if (saveTimer > 0.02f) // 0.02초마다 저장
		{
			SavePlayerPos();
			saveTimer = 0.0f;
		}

		if (player->dashTimer <= 0.f)
		{
			if (stageState < StageBoss)
			{
				player->spd = player->originalSpd;
			}
			else
			{
				player->spd = player->originalSpd = 800;
			}

			shadowIndex = 0; // 잔상 초기화
			player->playerState = INVINCIBLEBONUS;
		}

		if (player->dashTimer <= -player->dashInvincibleTimeMax)	// 대쉬끝난 후 약간의 무적타임
		{
			player->isDashing = 0;
			player->playerState = NORMAL;
		}
	}
}

void DestroyPlayer()
{
	free(player);
	player = NULL;
}

void ChangePlayerSize()
{
	float targetSize = playerOriSize * 0.9f;

	if (playerSizeState == 0)
	{
		player->size -= GetDt() * sizingSpeed;

		if (player->size <= targetSize)
		{
			playerSizeState = -1;
		}
	}
	else
	{
		player->size += GetDt() * sizingSpeed;

		if (playerOriSize < player->size)
		{
			playerSizeState = 0;
		}
	}
}