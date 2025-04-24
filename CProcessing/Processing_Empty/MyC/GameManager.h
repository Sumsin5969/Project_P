#pragma once
#include "../Defines.h"
#include "../player.h"
#include "../Enemy.h"
#include "../Obstacle.h"

void InitGameManager();
void GMUpdate();
void GMLateUpdate();
void FreeAll();
float GetDt();

PlayerState GetPlayerState();
StageState GetStageState();

GameState GetGameState();
void SetGameState(GameState targetGameState);

void CheckGameState();
void AllBulletInit(Bullet* _bullet);
void CheckPlayerState();

void SavePlayerPos();


StageState stageState;
GameState gameState;

PlayerCharacter* player;

CP_Vector pcShadow[100]; // 잔상용
int shadowIndex;
