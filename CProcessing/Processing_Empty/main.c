
#include <stdio.h>
#include "cprocessing.h"
#include "./MyC/GameManager.h"
#include "SoundManager.h"
#include "./MyC/Collision.h"

#include "Defines.h"

char buffer[200];


void PrintMainMenu();

void game_init(void)
{
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

	//CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_TOP);
	CP_Settings_Fill(CP_Color_Create(238, 200, 200, 255));

	sprintf_s(buffer, sizeof(buffer), "Press [Enter] key To Play");
	CP_Font_DrawText(buffer, WIDTH / 2, HEIGHT / 2);

	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	sprintf_s(buffer, sizeof(buffer), "Idiot Seo MinSu");

	CP_Font_DrawText(buffer, WIDTH / 2, HEIGHT / 2 + 200);

	if (CP_Input_KeyReleased(KEY_ENTER))
	{
		// 죄다 초기화해주면 될듯 하다.

		// Text 띄워준다.



		stageState = StageOne;
		gameState = Play;
	}
}

