#include <cprocessing.h>
#include "SoundManager.h"


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



void LoadSounds()
{
	titleBGM = CP_Sound_Load("Assets/minsu.wav");
	TestSound = CP_Sound_Load("Assets/TestSound.wav");
	gameStartSound = CP_Sound_Load("Assets/GameStart.wav");
	stageDownSound = CP_Sound_Load("Assets/StageDown.wav");
	stageUpSound = CP_Sound_Load("Assets/StageUp.mp3");
	/*stageSound_1 = CP_Sound_Load("Assets/StageSound1.wav");
	stageSound_2 = CP_Sound_Load("Assets/StageSound2.wav");
	stageSound_3 = CP_Sound_Load("Assets/StageSound3.wav");
	stageSound_4 = CP_Sound_Load("Assets/StageSound4.wav");
	stageSound_5 = CP_Sound_Load("Assets/StageSound5.wav");
	stageSound_6 = CP_Sound_Load("Assets/StageSound6.wav");*/
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
		CP_Sound_PlayAdvanced(stageUpSound, 3, 1, FALSE, CP_SOUND_GROUP_SFX);
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