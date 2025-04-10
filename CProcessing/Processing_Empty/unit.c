#include <stdio.h>
#include "cprocessing.h"
#include "unit.h"

#define UP CP_Input_KeyDown(KEY_UP)
#define DOWN CP_Input_KeyDown(KEY_DOWN)
#define LEFT CP_Input_KeyDown(KEY_LEFT)
#define RIGHT CP_Input_KeyDown(KEY_RIGHT)

float player_spd = 400;
CP_Vector player_pos;

void SetPosition(float w, float h) // 실행 시 위치 초기화
{
	player_pos = CP_Vector_Set(w / 2, h / 2);
}
void PlayerMove(void) // 방향키로 이동, 쉬프트, 스페이스 
{
	float dt = CP_System_GetDt();
	CP_Vector direction = CP_Vector_Set(0, 0);

	if (UP)    direction.y -= 1;
	if (DOWN)  direction.y += 1;
	if (LEFT)  direction.x -= 1;
	if (RIGHT) direction.x += 1;

	direction = CP_Vector_Normalize(direction);

	player_pos.x += direction.x * player_spd * dt;
	player_pos.y += direction.y * player_spd * dt;
}

void DrawPlayer(float x, float y)
{
	CP_Graphics_DrawCircle(x, y, 50);
}

void InitChar(void)
{
	player_pos = CP_Vector_Set(0,0);
	player_spd = 400;
}

void ChangeSpeed(void)
{
	if (CP_Input_KeyDown(KEY_5)) player_spd = 400;
	if (CP_Input_KeyDown(KEY_4)) player_spd = 300;
	if (CP_Input_KeyDown(KEY_3)) player_spd = 200;
	if (CP_Input_KeyDown(KEY_2)) player_spd = 100;
	if (CP_Input_KeyDown(KEY_1)) player_spd = 50;
	if (CP_Input_KeyDown(KEY_6)) player_spd = 500;
	if (CP_Input_KeyDown(KEY_6)) player_spd = 600;
	if (CP_Input_KeyDown(KEY_7)) player_spd = 700;
	if (CP_Input_KeyDown(KEY_8)) player_spd = 800;
	if (CP_Input_KeyDown(KEY_9)) player_spd = 900;
}