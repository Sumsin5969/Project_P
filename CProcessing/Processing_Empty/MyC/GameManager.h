#pragma once
#include "../Defines.h"
#include "../player.h"
#include "../Enemy.h"
#include "../Obstacle.h"
void InitGameManager();
void GMUpdate();
void GMLateUpdate();
void FreeAll();
float GetDt();

PlayerState GetPlayerState();
StageState GetStageState();

GameState GetGameState();
void SetGameState(GameState targetGameState);

void CheckGameState();
void CheckPlayerState();

void SavePlayerPos();
void SaveEnemyPos();
void InitEnemies();
void InitAll();


StageState stageState;
GameState gameState;

PlayerCharacter* player;

CP_Vector pcShadow[100]; // 잔상용
int shadowIndex;

CP_Vector enemyShadow[100];
int enemyShadowIndex;

extern Obstacle wall[MAX];
extern Obstacle bosswall[11];
extern Obstacle tutorialwall[3];
extern Obstacle startbox[2];

void Update_Tutorial();
void Update_StageOne();
void Update_StageTwo();
void Update_StageThree();
void Update_StageFour();
void Update_StageFive();
void Update_StageSix();
void Update_StageBoss();
// 적 업데이트 함수들을 묶은 함수

void SetTutorialImage(CP_Image img);
void SetEndingImage(CP_Image img);

void Update_Enemy();

void DrawEndingImage(float width, float height);
