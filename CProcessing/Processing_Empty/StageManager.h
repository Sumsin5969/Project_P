#pragma once

void PreviousStage();
void NextStage();
void OnPlayerHit();
void StageTimer();
void StageTimerLevelUp(); // 스테이지 상승할 때 
void StageTimerLevelDown(); // 스테이지 다운할 때

void StageTimerReset();
void SetStageTime(float _time);
void DefaultTimerUI();

extern float stageTime;