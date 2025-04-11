#include <stdio.h>
#include "cprocessing.h"
#include "unit.h"
#define UP CP_Input_KeyDown(KEY_UP)
#define DOWN CP_Input_KeyDown(KEY_DOWN)
#define LEFT CP_Input_KeyDown(KEY_LEFT)
#define RIGHT CP_Input_KeyDown(KEY_RIGHT)
PlayerCharacter player;
Enemy enemy;

void PlayerInit(void)
{
	player.isDashing = 0;
	player.dashTime = 0.3f;
	player.dashSpeedBoost = 1000.f;
	player.size = 25.f;
}
void EnemyInit(void)
{
	enemy.appTime = 10.f;
	enemy.isAttack = 0;
	enemy.spd = 100.f;
	enemy.pos.x = 0;
	enemy.pos.y = 0;
	enemy.size = 50.f;
}
void PlayerMove(void) // 방향키를 입력받으면 플레이어를 이동시키는 함수
{
	player.direction.x = 0;
	player.direction.y = 0;
	float dt = CP_System_GetDt();
	

	if (UP)    player.direction.y -= 1;
	if (DOWN)  player.direction.y += 1;
	if (LEFT)  player.direction.x -= 1;
	if (RIGHT) player.direction.x += 1;

	player.direction = CP_Vector_Normalize(player.direction);

	player.pos.x += player.direction.x * player.spd * dt;
	player.pos.y += player.direction.y * player.spd * dt;
}

void DrawPlayer(float x, float y) // 플레이어 캐릭터를 그려주는 함수
{
	CP_Settings_Fill(CP_Color_Create(36, 235, 238, 255));
	CP_Graphics_DrawCircle(x, y, player.size);
}

void InitChar(float x, float y) // 디버깅용 위치 초기화 함수
{
	player.pos = CP_Vector_Set(x/2, y/2);
	player.spd = 400;
}

void ChangeSpeed(void) // 디버깅용 속도 제어 함수
{
	if (CP_Input_KeyDown(KEY_1)) player.spd = 50;
	if (CP_Input_KeyDown(KEY_2)) player.spd = 100;
	if (CP_Input_KeyDown(KEY_3)) player.spd = 200;
	if (CP_Input_KeyDown(KEY_4)) player.spd = 300;
	if (CP_Input_KeyDown(KEY_5)) player.spd = 400;
	if (CP_Input_KeyDown(KEY_6)) player.spd = 500;
	if (CP_Input_KeyDown(KEY_7)) player.spd = 600;
	if (CP_Input_KeyDown(KEY_8)) player.spd = 700;
	if (CP_Input_KeyDown(KEY_9)) player.spd = 800;
	if (CP_Input_KeyDown(KEY_0)) player.spd = 900;
}

void Dash(void)
{
	float dt = CP_System_GetDt();

	if (CP_Input_KeyTriggered(KEY_LEFT_SHIFT) && !player.isDashing)
	{
		if (player.direction.x == 0 && player.direction.y == 0)
		{
			return;
		}
		player.isDashing = 1;
		player.dashTimer = player.dashTime;
		player.originalSpd = player.spd;
		player.spd += player.dashSpeedBoost;
		player.dashDecayRate = player.dashSpeedBoost / player.dashTimer;
	}

	if (player.isDashing)
	{
		player.dashTimer -= dt;
		player.spd -= player.dashDecayRate * dt;

		if (player.dashTimer <= 0.f)
		{
			player.spd = player.originalSpd;
			player.isDashing = 0;
		}
	}
	
}