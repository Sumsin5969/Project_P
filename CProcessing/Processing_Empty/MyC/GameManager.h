#pragma once
#include "../Defines.h"

void InitGameManager();
void GMUpdate();
void GMLateUpdate();
void FreeAll();
PlayerState GetPlayerState();
StageState GetStageState();

GameState GetGameState();
void SetGameStage(StageState targetGameState);

extern PlayerState playerState;
extern StageState stageState;
extern GameState gameState;
