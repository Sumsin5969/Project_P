#pragma once
#define WIDTH 1760
#define HEIGHT 990
#define WALLWIDTHSIZE 30
#define WALLHEIGHTSIZE 24
#define MAX_ENEMIES 10
#define MAX_BULLETS_PER_ENEMY 300
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
	INVINCIBLE
} PlayerState;

typedef enum GameState
{
	Play,
	Stop,
	ChangingStage
} GameState;

typedef enum StageState
{
	MainMenu,
	GameOver,
	GameClear,
	StageOne,
	StageTwo,
	StageThree,
	StageFour,
	StageFive,
	StageBoss
} StageState;
