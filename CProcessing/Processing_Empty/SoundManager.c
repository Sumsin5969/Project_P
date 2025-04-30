#include <cprocessing.h>
#include "SoundManager.h"

void LoadSounds()
{
	titleBGM = CP_Sound_Load("Assets/minsu.wav");
	TestSound = CP_Sound_Load("Assets/TestSound.wav");
}

void FreeAllSound()
{
	
}