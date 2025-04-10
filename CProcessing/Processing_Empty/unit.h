#pragma once


typedef struct PlayerCharacter
{
    CP_Vector pos;
    float spd;
} PlayerCharacter;

void PlayerMove(void);
void DrawPlayer(float x, float y);
void InitChar(float, float);
void ChangeSpeed(void);