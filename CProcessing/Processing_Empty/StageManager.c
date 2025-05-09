#include <stdio.h>
#include "Defines.h"
#include "StageManager.h"
#include "MyC/ZoomCamera.h"
#include "MyC/GameManager.h"
#include "Player.h"
#include "SoundManager.h"
#include "math.h"
#include <corecrt.h>

const float defaultTime = 20.f;
char timeBuffer[10];
float stageTime = 20.f; // 타이머
float timeAcc = 0.f; // 가중치
float stageTimeStart = 0.f;

void PreviousStage()
{
	//zoomin
	ZoomIn();
	//적 캐릭터 및 공격 일시정지

	//캐릭터의 포지션을 카메라의 포지션으로 초기화

	//몇 초 후 재생
}

void NextStage()
{

}

void OnPlayerHit()
{
	// prevstg ㄱㄱ
	// 무적 ㄱㄱ
}

void DefaultTimerUI()
{
	CP_Settings_Fill(CP_Color_Create(36, 235, 238, 200));
	CP_Font_DrawText(timeBuffer, WIDTH / 2, 50);
	sprintf_s(timeBuffer, sizeof(timeBuffer), "%.1f", stageTime);
}

void StageTimer() // Play일때 기본적으로 작동되는 타이머
{
	float dt = CP_System_GetDt();

	if (stageTime <= 0)		// 바뀌는곳 찾아가기 힘들다. 어디서 바뀌는지 뭘로바뀌는지 안명확하다!
	{
		gameState = StageUp;

		SetZoomOutTargetRate();

		return;
	}

	stageTime -= dt; // 타이머 흐르게

	if (stageTime <= 0)
	{
		stageTime = 0.f;
	}
	/*CP_Font_DrawText(timeBuffer, WIDTH / 2, 30);
	sprintf_s(timeBuffer, sizeof(timeBuffer), "%.1f", stageTime);*/


}

void StageTimerLevelUp() // 스테이지 상승할 때 
{
	float dt = CP_System_GetDt();

	timeAcc += dt;

	float t = timeAcc / 2;

	if (t > 1.f) t = 1.f;

	stageTime = defaultTime * (t * t, (float)pow(t, 2.0));

	ZoomOutSlightly(t * t);

	PlayStageUpSound();

	CancleBGMPlaying();

	if (t >= 1.f)
	{
		if (stageState == StageBoss)
		{
			SetGameState(GameClear);
			printf("게임클리어 게임스테이트 = 게임클리어");
			return;
		}

		stageTime = defaultTime;
		timeAcc = 0.f;


		stageState++;

		if (stageState == StageBoss)
		{
			stageTime = 100.f;
			player->spd *= 2;
			player->dashSpeedBoost *= 2;
		}

		ZoomOutForce();
		SetZoom(stageState);
		CancleSoundPlaying();

		PlayStageBGM(stageState);

		SetGameState(Play);
	}

	/*CP_Font_DrawText(timeBuffer, WIDTH / 2, 30);
	sprintf_s(timeBuffer, sizeof(timeBuffer), "%.1f", stageTime);*/
}

void StageTimerReset()
{
	stageTime = defaultTime;
}


void StageTimerLevelDown() // 스테이지 다운할 때
{
	float dt = CP_System_GetDt();

	timeAcc += dt;

	float t = timeAcc;

	if (t > 1.f) t = 1.f;

	float delta = defaultTime - stageTimeStart;

	stageTime = stageTimeStart + delta * (t * t);  // 가속도 형태로 증가

	ZoomInSlightly(delta * (t / 2 * t / 2));

	CameraShaking();
	/*CP_Font_DrawText(timeBuffer, WIDTH / 2, 30);
	sprintf_s(timeBuffer, sizeof(timeBuffer), "%.1f", stageTime);*/

	PlayStageDownSound();

	if (t >= 1.f)
	{
		stageTime = defaultTime;
		timeAcc = 0.f;
		ZoomInForce(); // Setzoom쓰면 필요없음;
		SetZoom(stageState);

		InitAll();
		ResetCameraShakeTime();
		CancleSoundPlaying();
		CancleBGMPlaying();


		if (stageState < StageOne)
		{
			InitAll();
			InitCamera();
			CP_Sound_StopGroup(CP_SOUND_GROUP_SFX);
			SetGameState(GameOver);
		}
		else
		{
			SetGameState(Play);
			CP_Sound_StopGroup(CP_SOUND_GROUP_SFX);

			PlayStageBGM(stageState);
		}

	}

}

void SetStageTime(float _time)
{
	stageTime = _time;
}