#pragma once
#include <cprocessing.h>
#include "Defines.h"

extern CP_Sound titleBGM;
extern CP_Sound TestSound;
extern CP_Sound gameStartSound;

void LoadSounds();

void FreeAllSound();

void PlayStageDownSound();

void PlayStageUpSound();

void FreeBGM();

void CancleSoundPlaying();
void CancleBGMPlaying();


void PlayStageBGM(StageState stage);

void StopBGM();
