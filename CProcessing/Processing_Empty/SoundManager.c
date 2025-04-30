#include <cprocessing.h>
#include "SoundManager.h"


CP_Sound titleBGM;
CP_Sound TestSound;
CP_Sound gameStartSound;
CP_Sound stageDownSound;

CP_BOOL soundPlaying = FALSE;

void LoadSounds()
{
	titleBGM = CP_Sound_Load("Assets/minsu.wav");
	TestSound = CP_Sound_Load("Assets/TestSound.wav");
	gameStartSound = CP_Sound_Load("Assets/GameStart.wav");
	stageDownSound = CP_Sound_Load("Assets/StageDown.wav");
}

void PlayStageDownSound()
{
	//CP_Sound_StopAll();
	if (soundPlaying == FALSE)
	{
		CP_Sound_StopGroup(CP_SOUND_GROUP_MUSIC);
		CP_Sound_PlayAdvanced(stageDownSound, 5, 1, FALSE, CP_SOUND_GROUP_SFX);
		soundPlaying = TRUE;
	}
	else
	{

	}
}

void CancleSoundPlaying()
{
	soundPlaying = FALSE;
}

void FreeAllSound()
{

}

void FreeBGM()
{
	//CP_Sound_StopGroup()
}