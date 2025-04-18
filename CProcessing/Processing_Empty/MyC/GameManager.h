#pragma once
#include "../Defines.h"

void InitGameManager();
void GMUpdate();
void GMLateUpdate();
void FreeAll();
PlayerState GetPlayerState();
StageState GetStageState();