#pragma once
#define WIDTH 1760
#define HEIGHT 990
#define WALLWIDTHSIZE 20
#define WALLHEIGHTSIZE 20
#define MAX_ENEMIES 4
#define MAX_BULLETS_PER_ENEMY 30

#define STAGECLEARTIME 30

typedef enum ObstacleType
{
	WALL_LEFT,
	WALL_RIGHT,
	WALL_TOP,
	WALL_BOTTOM,
	MAX

} ObstacleType;

typedef enum UnitType
{
	PLAYERCHARACTER = 0,
	ENEMYCHARACTER,
	OBSTACLE,
	BOSS,
} E_UnitType;

typedef enum PlayerState
{
	HIT,
	NORMAL,
	INVINCIBLE // 무적
} PlayerState;

typedef enum GameState
{
	Play,
	Stop,
	ChangingStage,
	StageUp,
	StageDown,
	PlayerDead,
	MainMenu,
	GameOver,
	GameClear,
} GameState;

typedef enum StageState
{
	StageOne,
	StageTwo,
	StageThree,
	StageFour,
	StageFive,
	StageBoss
} StageState;

typedef enum
{
	B_PlayerDirection,
	B_Circle,
	B_Laser,
} BulletType;