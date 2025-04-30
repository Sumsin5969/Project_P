#pragma once
#include <cprocessing.h>


extern CP_Sound titleBGM;
extern CP_Sound TestSound;
extern CP_Sound gameStartSound;

void LoadSounds();

void FreeAllSound();

void PlayStageDownSound();

void FreeBGM();

void CancleSoundPlaying();