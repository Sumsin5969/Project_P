#pragma once
#define WIDTH 1760
#define HEIGHT 990
#define WALLWIDTHSIZE 30
#define WALLHEIGHTSIZE 24

typedef enum WallDirect
{
	LEFT,
	RIGHT,
	TOP,
	BOTTOM
} WallDirect;

typedef enum UnitType
{
	PLAYERCHARACTER = 0,
	ENEMYCHARACTER,
	OBSTACLE,
	BOSS,
} E_UnitType;
