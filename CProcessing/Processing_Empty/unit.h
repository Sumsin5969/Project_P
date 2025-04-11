#pragma once
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
extern PlayerCharacter player;
<<<<<<< Updated upstream
#pragma once
=======

>>>>>>> Stashed changes
typedef struct Enemy
{
	CP_Vector pos;
	float spd;
	int isAttack;
	float appTime;
	float size;
} Enemy;
extern Enemy enemy;

void PlayerMove(void);
void DrawPlayer(float x, float y);
void InitChar(float, float);
void ChangeSpeed(void);
void Dash(void);
void PlayerInit(void);
void DrawWall(void);