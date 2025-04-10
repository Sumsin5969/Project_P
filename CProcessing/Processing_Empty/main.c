
#include "cprocessing.h"
#include "main.h"

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900
#define PLAYER_SPEED 400

CP_Vector player_position;

void game_init(void) 
{
	// initialize variables and CProcessing settings for this gamestate
	
}

void game_update(void) {
	float dt = CP_System_GetDt();

	// Very bad player movement code!
	if (CP_Input_KeyDown(KEY_W)) player_position.y -= PLAYER_SPEED * dt;
	if (CP_Input_KeyDown(KEY_S)) player_position.y += PLAYER_SPEED * dt;
	if (CP_Input_KeyDown(KEY_A)) player_position.x -= PLAYER_SPEED * dt;
	if (CP_Input_KeyDown(KEY_D)) player_position.x += PLAYER_SPEED * dt;

	CP_Graphics_ClearBackground(CP_Color_Create(50, 50, 50, 0));

	CP_Settings_BlendMode(CP_BLEND_ADD);

	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Graphics_DrawCircle(player_position.x, player_position.y, 300);

	// Add some more random 'light sources'
	CP_Graphics_DrawCircle(100, 100, 100);
	CP_Graphics_DrawCircle(1300, 800, 400);
	CP_Graphics_DrawCircle(200, 300, 100);
	CP_Graphics_DrawCircle(200, 300, 100);

	//
	// Scene
	//
	// Multipy the rest of the scene. 
	// 
	CP_Settings_BlendMode(CP_BLEND_MULTIPLY);
	// This is the player
	CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
	CP_Graphics_DrawCircle(player_position.x, player_position.y, 100);

	// These are some random things on the scene
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Graphics_DrawRect(100, 100, 50, 50);
	CP_Graphics_DrawRect(100, 300, 50, 50);
	CP_Graphics_DrawRect(1400, 600, 50, 50);
	CP_Graphics_DrawRect(1300, 100, 50, 50);

	PrintFrameInfo();

	// NOTE: If you want the player to overlap the 'random things'
	// the 'normal' way (i.e. using CP_BLEND_APLHA), you might have to do
	// some collision detection with the player and switch the blend
	// mode accordingly. We'll leave this as an exercise to the reader.

	
}

void game_exit(void) {
}

int main(void)
{
	CP_System_SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	CP_Engine_Run();
	return 0;
}