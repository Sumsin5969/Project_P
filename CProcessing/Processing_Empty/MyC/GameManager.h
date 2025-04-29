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
void CheckPlayerState();

void SavePlayerPos();
void InitEnemies();
void InitAll();


StageState stageState;
GameState gameState;

PlayerCharacter* player;

CP_Vector pcShadow[100]; // 잔상용
int shadowIndex;

extern Obstacle wall[MAX];

void Update_StageOne();
void Update_StageTwo();
void Update_StageThree();
void Update_StageFour();
void Update_StageBoss();
void Update_Enemy();