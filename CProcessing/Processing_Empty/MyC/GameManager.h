#pragma once
#include "../Defines.h"
#include "../Player.h"

void InitGameManager();
void GMUpdate();
void GMLateUpdate();
void FreeAll();
float GetDt();

PlayerState GetPlayerState();
StageState GetStageState();

GameState GetGameState();
void SetGameState(GameState targetGameState);

StageState stageState;
GameState gameState;

PlayerCharacter* player;
