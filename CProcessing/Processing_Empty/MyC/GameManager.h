#pragma once
#include "../Defines.h"
#include "../player.h"

void InitGameManager();
void GMUpdate();
void GMLateUpdate();
void FreeAll();
PlayerState GetPlayerState();
StageState GetStageState();

GameState GetGameState();
void SetGameState(GameState targetGameState);

void CheckGameState();
void CheckPlayerState();

StageState stageState;
GameState gameState;

PlayerCharacter* player;
