#include <stdio.h>
#include "StageManager.h"
#include "MyC/ZoomCamera.h"
#include "MyC/GameManager.h"
#include "Player.h"
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

char timeBuffer[10];
float stageTime = 30.f; // 타이머
float timeAcc = 0.f; // 가중치
void StageTimer()
{
	float dt = CP_System_GetDt();
	if (GetGameState() == Play)
	{
		sprintf_s(timeBuffer, sizeof(timeBuffer), "%.1f", stageTime);
		CP_Font_DrawText(timeBuffer, WIDTH / 2, 30);
		stageTime -= dt; // 타이머 흐르게
	}
	else
	{
		sprintf_s(timeBuffer, sizeof(timeBuffer), "%.1f", stageTime);
		CP_Font_DrawText(timeBuffer, WIDTH / 2, 30);
		timeAcc += dt;
		stageTime += dt * timeAcc;
		if (stageTime >= 30.f)
		{
			stageTime = 30.f;
			timeAcc = 0.f;
		}
	}
}