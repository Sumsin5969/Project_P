#pragma once
#define WIDTH 1760
#define HEIGHT 990
#define WALLWIDTHSIZE 20
#define WALLHEIGHTSIZE 20
#define MAX_ENEMIES 4
#define MAX_CIRCLE_ENEMIES 4
#define MAX_BULLETS_PER_ENEMY 50
#define MAGAZINE 10
#define STAGECLEARTIME 30
#define ZOOMSPEED 1
#define ENEMY_COLOR() CP_Color_Create(200,1,147,255)	// 이렇게도 함수를 디파인할 수 있다.
//CP_Color defaultColor = { 200,1,147,255 };			// 사실 이렇게 쓰는게 더 깔끔하겠지 하지만 include하기 싫으니까 


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
	BOSSCHARACTER,
} UnitType;

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
	StageBoss,
} StageState;

typedef enum
{
	LD_UP,
	LD_DOWN,
	LD_LEFT,
	LD_RIGHT,
} LaserDirection;

typedef enum
{
	TOPLEFT,
	TOPRIGHT,
	BOTTOMLEFT,
	BOTTOMRIGHT
} EnemyDestination;

