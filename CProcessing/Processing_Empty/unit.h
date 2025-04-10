#pragma once

struct PlayerCharacter
{
	float posX;
	float posY;
	float speed;
};

void SetPosition(float w, float h);
void PlayerMove(void);
void DrawPlayer(float x, float y);
void InitChar(void);
void ChangeSpeed(void);