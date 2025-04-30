#include <cprocessing.h>
#include "SoundManager.h"


CP_Sound titleBGM;
CP_Sound TestSound;

void LoadSounds()
{
	titleBGM = CP_Sound_Load("Assets/minsu.wav");
	TestSound = CP_Sound_Load("Assets/TestSound.wav");

}

void FreeAllSound()
{
	
}

void FreeBGM()
{
	//CP_Sound_StopGroup()
}