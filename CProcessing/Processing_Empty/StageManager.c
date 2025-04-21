#include <stdio.h>
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

void StageTimer()
{
	float dt = CP_System_GetDt();

	if (GetGameState() == Play)
	{
		stageTime -= dt; // 타이머 흐르게
		stageTimeStart = stageTime;
	}

	else if (GetGameState() == StageDown)
	{
		timeAcc += dt;

		// 최대 2초간 가속적으로 증가
		float t = timeAcc / 2.f;

		if (t > 1.f) t = 1.f;

		float delta = 30.f - stageTimeStart;

		stageTime = stageTimeStart + delta * (t * t);  // 가속도 형태로 증가

		if (t >= 1.f)
		{
			stageTime = 30.f;
			timeAcc = 0.f;
			SetGameState(Play);
		}
	}


	CP_Font_DrawText(timeBuffer, WIDTH / 2, 30);
	sprintf_s(timeBuffer, sizeof(timeBuffer), "%.1f", stageTime);
}

void CheckPlayerState() // 플레이어의 상태를 체크해서 게임의 진행사항을 바꿔준다.
{
	switch (player->playerState)
	{
	case HIT:
		printf("플레이어 HIT \n");
		break;

	case NORMAL:
		printf("플레이어 NORMAL \n");
		break;

	case INVINCIBLE:
		printf("플레이어 INVINCIBLE 무적 \n");
		break;

	default:
		break;
	}
}

void CheckGameState()
{
}
