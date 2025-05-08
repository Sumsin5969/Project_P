
#include <stdio.h>
#include "cprocessing.h"

#include "./MyC/GameManager.h"
#include "./MyC/Collision.h"
#include "Defines.h"
#include "SoundManager.h"


char buffer[200];
CP_Image titleImage;


void PrintMainMenu();

void game_init(void)
{
	titleImage = CP_Image_Load("./Assets/TitleImage.png");

	LoadSounds();

	//CP_Sound_Play(titleBGM);
	//CP_Sound_Play(TestSound);


	//CP_Sound_PlayMusic(TestSound);

	SetGameState(MainMenu);
	InitGameManager();
	CP_System_SetFrameRate(100);
}

void game_update(void)
{
	if (gameState == GameOver || gameState == MainMenu)
	{
		PrintMainMenu();
		return;
	}

	GMUpdate();

	GMLateUpdate();
}

void game_exit(void)
{
	FreeAll();
}

int main(void)
{
	CP_System_SetWindowSize(WIDTH, HEIGHT);
	CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	CP_Engine_Run();
	return 0;
}

void PrintMainMenu()
{
	CP_Graphics_ClearBackground(CP_Color_Create(153, 255, 255, 0));

	CP_Image_Draw(titleImage, WIDTH/2, HEIGHT/2, 1760, 990, 255);

	//CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_TOP);
	CP_Settings_Fill(CP_Color_Create(0, 255, 00, 255));

	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);

	CP_Settings_TextSize(60);

	sprintf_s(buffer, sizeof(buffer), "Press [Enter] key To Play");
	
	CP_Font_DrawText(buffer, WIDTH / 2, HEIGHT / 2);

	if (CP_Input_KeyReleased(KEY_ENTER))
	{
		// 죄다 초기화해주면 될듯 하다.

		// Text 띄워준다.
		CP_Sound_PlayAdvanced(gameStartSound, 2, 1, FALSE, CP_SOUND_GROUP_SFX);
		CP_Sound_PlayAdvanced(titleBGM, 1, 1, FALSE, CP_SOUND_GROUP_1);

		stageState = StageOne;
		gameState = Play;
	}

	CP_Settings_TextSize(50);
}

