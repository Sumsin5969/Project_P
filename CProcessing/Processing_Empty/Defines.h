#pragma once
#define WIDTH 1760
#define HEIGHT 990
#define WALLWIDTHSIZE 20
#define WALLHEIGHTSIZE 20
#define MAX_ENEMIES 4
#define MAX_CIRCLE_ENEMIES 4
#define MAX_BULLETS_PER_ENEMY 20
#define MAX_LASERS 200
#define CLIP 10
#define BOSSCLIP 20
#define STAGECLEARTIME 20
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
	BOSSCHARACTER,
	OBSTACLE,
} UnitType;

typedef enum PlayerState
{
	HIT, // Is it really player state???
	NORMAL,
	INVINCIBLE, // 무적
	INVINCIBLEBONUS		// 무적보너스
} PlayerState;

typedef enum GameState
{
	Play,
	StageUp, // Play state에 종속된
	StageDown, // Play state에 종속된
	MainMenu,
	GameOver,
	GameClear,
} GameState;

typedef enum StageState
{
	Tutorial,
	StageOne,
	StageTwo,
	StageThree,
	StageFour,
	StageFive,
	StageSix,
	StageBoss,
	StageLastIndex
} StageState;

typedef enum
{
	LD_UP,
	LD_DOWN,
	LD_LEFT,
	LD_RIGHT
} LaserDirection;

typedef enum
{
	TOPLEFT,
	TOPRIGHT,
	BOTTOMLEFT,
	BOTTOMRIGHT
} EnemyDestination;

typedef enum
{
	TITLEBGM,
	BGM,
	STAGE1
} SoundType;

typedef enum
{
	BOSSWARNING,
	APPEAR,
	DISAPPEAR,
	DEAD,
} BossState;
