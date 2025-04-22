#include <stdio.h>
#include "Defines.h"
#include "StageManager.h"
#include "MyC/ZoomCamera.h"
#include "MyC/GameManager.h"
#include "Player.h"

char timeBuffer[10];
float stageTime = 30.f; // 타이머
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

void StageTimer() // Play일때 기본적으로 작동되는 타이머
{
	float dt = CP_System_GetDt();

	stageTime -= dt; // 타이머 흐르게

	if (stageTime <= 0)
	{
		SetZoomOutTargetRate();
		gameState = StageUp;
		return;
	}

	CP_Font_DrawText(timeBuffer, WIDTH / 2, 30);
	sprintf_s(timeBuffer, sizeof(timeBuffer), "%.1f", stageTime);
}

void StageTimerLevelUp() // 스테이지 상승할 때 
{
	float dt = CP_System_GetDt();

	timeAcc += dt;

	// 최대 2초간 가속적으로 증가
	float t = timeAcc / 2.f;

	if (t > 1.f) t = 1.f;

	stageTime = (t * t);  // 가속도 형태로 증가

	ZoomOutSlightly(t * t);

	if (t >= 1.f)
	{
		stageTime = 30.f;
		timeAcc = 0.f;

		ZoomOutForce();
		SetGameState(Play);
	}

	CP_Font_DrawText(timeBuffer, WIDTH / 2, 30);
	sprintf_s(timeBuffer, sizeof(timeBuffer), "%.1f", stageTime);
}



void StageTimerLevelDown() // 스테이지 다운할 때
{
	float dt = CP_System_GetDt();

	timeAcc += dt;

	// 최대 2초간 가속적으로 증가
	float t = timeAcc / 2.f;

	if (t > 1.f) t = 1.f;

	float delta = 30.f - stageTimeStart;

	stageTime = stageTimeStart + delta * (t * t);  // 가속도 형태로 증가

	ZoomInSlightly(delta * (t * t));

	if (t >= 1.f)
	{
		stageTime = 30.f;
		timeAcc = 0.f;
		ZoomInForce();
		SetGameState(Play);
	}
	CP_Font_DrawText(timeBuffer, WIDTH / 2, 30);
	sprintf_s(timeBuffer, sizeof(timeBuffer), "%.1f", stageTime);
}

void SetStageTime(float _time)
{
	stageTime = _time;
}