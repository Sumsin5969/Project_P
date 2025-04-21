#include <stdio.h>
#include "StageManager.h"
#include "MyC/ZoomCamera.h"
#include "MyC/GameManager.h"
#include "Player.h"

char timeBuffer[10];
float stageTime = 30.f; // 타이머
float timeAcc = 0.f; // 가중치

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

void StageTimer()
{
	float dt = CP_System_GetDt();

	if (GetGameState() == Play)
	{
		stageTime -= dt; // 타이머 흐르게
	}

	else if (GetGameState() == StageDown)
	{
		timeAcc += dt;

		float maxTime = 30.f;
		float remaining = maxTime - stageTime;
		float t = timeAcc / 5.f; // 0~1 구간
		if (t > 1.f) t = 1.f;

		stageTime = maxTime - remaining * (1.f - t * t); // 점점 증가 (곡선)

		if (timeAcc >= 5.f || stageTime >= maxTime)
		{
			stageTime = maxTime;
			timeAcc = 0.f;
			SetGameStage(Play);
		}

	}

	CP_Font_DrawText(timeBuffer, WIDTH / 2, 30);
	sprintf_s(timeBuffer, sizeof(timeBuffer), "%.1f", stageTime);
}
