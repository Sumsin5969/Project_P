#pragma once
#include "../Defines.h"
#include "../Player.h"

void InitGameManager();
void GMUpdate();
void GMLateUpdate();
void FreeAll();
PlayerState GetPlayerState();
StageState GetStageState();

GameState GetGameState();
void SetGameState(GameState targetGameState);

extern PlayerState playerState;
extern StageState stageState;
extern GameState gameState;

PlayerCharacter* player;
