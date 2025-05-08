#include <cprocessing.h>
#include "SoundManager.h"
#include "Defines.h"


CP_Sound titleBGM;
CP_Sound TestSound;
CP_Sound gameStartSound;
CP_Sound stageUpSound;
CP_Sound stageDownSound;

CP_Sound stageSound_1;
CP_Sound stageSound_2;
CP_Sound stageSound_3;
CP_Sound stageSound_4;
CP_Sound stageSound_5;
CP_Sound stageSound_6;
CP_Sound stageSound_7;

CP_BOOL soundPlaying = FALSE;
CP_BOOL bgmPlaying = FALSE;



void LoadSounds()
{
	titleBGM = CP_Sound_Load("Assets/minsu.wav");
	TestSound = CP_Sound_Load("Assets/TestSound.wav");
	gameStartSound = CP_Sound_Load("Assets/GameStart.wav");
	stageDownSound = CP_Sound_Load("Assets/StageDown.wav");
	stageUpSound = CP_Sound_Load("Assets/StageUp.mp3");
	stageSound_1 = CP_Sound_Load("Assets/Stage1.mp3");
	stageSound_2 = CP_Sound_Load("Assets/Stage2.mp3");
	stageSound_3 = CP_Sound_Load("Assets/Stage3.mp3");
	stageSound_4 = CP_Sound_Load("Assets/Stage4.mp3");
	stageSound_5 = CP_Sound_Load("Assets/Stage5.mp3");
	stageSound_6 = CP_Sound_Load("Assets/Stage6.mp3");
}

void PlayStageBGM(StageState stage)
{
	if (soundPlaying == TRUE) return;

	CP_Sound_StopGroup(CP_SOUND_GROUP_MUSIC);

	switch (stage)
	{
	case StageOne:
		CP_Sound_PlayAdvanced(stageDownSound, 1, 1, FALSE, CP_SOUND_GROUP_MUSIC);
		break;
	case  StageTwo:
		CP_Sound_PlayAdvanced(stageDownSound, 1, 1, FALSE, CP_SOUND_GROUP_MUSIC);
		break;
	case StageThree:
		CP_Sound_PlayAdvanced(stageDownSound, 1, 1, FALSE, CP_SOUND_GROUP_MUSIC);
		break;
	case StageFour:
		CP_Sound_PlayAdvanced(stageDownSound, 1, 1, FALSE, CP_SOUND_GROUP_MUSIC);
		break;
	case StageFive:
		CP_Sound_PlayAdvanced(stageDownSound, 1, 1, FALSE, CP_SOUND_GROUP_MUSIC);
		break;
	case StageSix:
		CP_Sound_PlayAdvanced(stageDownSound, 1, 1, FALSE, CP_SOUND_GROUP_MUSIC);
		break;
	}

	soundPlaying = TRUE;
}

void PlayStageDownSound()
{
	//CP_Sound_StopAll();
	if (soundPlaying == FALSE)
	{
		CP_Sound_StopGroup(CP_SOUND_GROUP_MUSIC);
		CP_Sound_PlayAdvanced(stageDownSound, 3, 1, FALSE, CP_SOUND_GROUP_SFX);
		soundPlaying = TRUE;
	}
	else
	{

	}
}

void PlayStageUpSound()
{
	if (soundPlaying == FALSE)
	{
		CP_Sound_StopGroup(CP_SOUND_GROUP_MUSIC);
		CP_Sound_PlayAdvanced(stageUpSound, 2, 1, FALSE, CP_SOUND_GROUP_SFX);
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

void CancleBGMPlaying()
{
	bgmPlaying = FALSE;
}

void FreeAllSound()
{

}

void FreeBGM()
{
	//CP_Sound_StopGroup()
}