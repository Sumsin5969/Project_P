#include <stdio.h>
#include "cprocessing.h"
#include "unit.h"

#define UP CP_Input_KeyDown(KEY_UP)
#define DOWN CP_Input_KeyDown(KEY_DOWN)
#define LEFT CP_Input_KeyDown(KEY_LEFT)
#define RIGHT CP_Input_KeyDown(KEY_RIGHT)

PlayerCharacter player;

void PlayerMove(void) // 방향키로 이동, 쉬프트, 스페이스 
{
	float dt = CP_System_GetDt();
	CP_Vector direction = CP_Vector_Set(0, 0);

	if (UP)    direction.y -= 1;
	if (DOWN)  direction.y += 1;
	if (LEFT)  direction.x -= 1;
	if (RIGHT) direction.x += 1;

	direction = CP_Vector_Normalize(direction);

	player.pos.x += direction.x * player.spd * dt;
	player.pos.y += direction.y * player.spd * dt;
}

void DrawPlayer(float x, float y)
{
	CP_Graphics_DrawCircle(x, y, 50);
}

void InitChar(float x, float y)
{
	player.pos = CP_Vector_Set(x/2, y/2);
	player.spd = 400;
}

void ChangeSpeed(void)
{
	if (CP_Input_KeyDown(KEY_1)) player.spd = 50;
	if (CP_Input_KeyDown(KEY_2)) player.spd = 100;
	if (CP_Input_KeyDown(KEY_3)) player.spd = 200;
	if (CP_Input_KeyDown(KEY_4)) player.spd = 300;
	if (CP_Input_KeyDown(KEY_5)) player.spd = 400;
	if (CP_Input_KeyDown(KEY_6)) player.spd = 500;
	if (CP_Input_KeyDown(KEY_6)) player.spd = 600;
	if (CP_Input_KeyDown(KEY_7)) player.spd = 700;
	if (CP_Input_KeyDown(KEY_8)) player.spd = 800;
	if (CP_Input_KeyDown(KEY_9)) player.spd = 900;
}

/*void Dash(void)
{
	if (CP_Input_KeyDown(KEY_SPACE))
}*/