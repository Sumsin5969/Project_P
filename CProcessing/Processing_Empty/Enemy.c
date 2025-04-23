#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Enemy.h"
#include "Defines.h"
#include "MyC/GameManager.h"
#include "MyC/ZoomCamera.h"
#include "MyC/Collision.h"

// 적과 탄환 초기화
// 
void EnemyInit_StageOne(Enemy* _enemy)
{
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		_enemy[i].isAttack = 0;
		_enemy[i].spd = 100.f;
		_enemy[i].size = 50.f;
		_enemy[i].active = 0;
		_enemy[i].fireDelay = 0.7f;
		_enemy[i].fireTime = 0.f;
		_enemy[i].magazine = 0;
		switch (i)
		{
		case 0:
			_enemy[i].pos.x = -850;
			_enemy[i].pos.y = -450;
			_enemy[i].enemyPosition = TOPLEFT;
			break;
		case 1:
			_enemy[i].pos.x = 850;
			_enemy[i].pos.y = -450;
			_enemy[i].enemyPosition = TOPRIGHT;
			break;
		case 2:
			_enemy[i].pos.x = -850;
			_enemy[i].pos.y = 450;
			_enemy[i].enemyPosition = BOTTOMLEFT;
			break;
		case 3:
			_enemy[i].pos.x = 850;
			_enemy[i].pos.y = 450;
			_enemy[i].enemyPosition = BOTTOMRIGHT;
			break;
		}

		for (int j = 0; j < MAX_BULLETS_PER_ENEMY; j++)
		{
			// Todo: 안쓰는 변수가 안생기도록 하는게 더 낫지만, 
			//       MJ 안쓰는 변수라도 초기화 하는 것을 권장
			PDBullets[i][j].projSpd = 400.f;
			PDBullets[i][j].projTime = 0.f;
			PDBullets[i][j].active = 0;
			PDBullets[i][j].size = 15.f;
			CircleBullets[i][j].projSpd = 100.f;
			CircleBullets[i][j].projTime = 0.f;
			CircleBullets[i][j].degree = j * (360.f / MAX_BULLETS_PER_ENEMY);
			CircleBullets[i][j].active = 0;
			CircleBullets[i][j].size = 3.f;
		}
	}
}
// 스테이지 2로 넘어갈 시 출현할 적을 gameinit에서 초기화
// Enemy속성들 2행의 1차원 배열로 초기화 할 거임
// todo: 스테이지별 적에게 할당할 탄환 배열 또 만들기
void EnemyInit_StageTwo(Enemy* _enemy)
{
	// pos x,y는 switch-case로 할 거임
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		_enemy[i].spd = 150.f;
		_enemy[i].fireTime = 0.f;
		_enemy[i].fireDelay = 3.f;
		_enemy[i].size = 50.f;
		_enemy[i].magazine = 0;
		_enemy[i].active = 0;
		switch (i)
		{
		case 0:
			_enemy[i].pos.x = -650;
			_enemy[i].pos.y = -350;
			_enemy[i].enemyPosition = TOPLEFT;
		case 1:
			_enemy[i].pos.x = -650;
			_enemy[i].pos.y = 350;
			_enemy[i].enemyPosition = BOTTOMLEFT;
		case 2:
			_enemy[i].pos.x = 650;
			_enemy[i].pos.y = 350;
			_enemy[i].enemyPosition = BOTTOMRIGHT;
		case 3:
			_enemy[i].pos.x = 650;
			_enemy[i].pos.y = -350;
			_enemy[i].enemyPosition = TOPRIGHT;
		}
		for (int j = 0; j < MAX_BULLETS_PER_ENEMY; j++)
		{
			
		}
	}
}
// Enemy를 움직여주는 함수: 반시계 방향으로 Enemy를 지속적으로 이동

void EnemyMove_StageOne(Enemy* enemy)
{
	float dt = GetDt() * (enemy->spd);
	if (enemy->enemyPosition == TOPLEFT)
	{
		enemy->pos.y += dt;
		// Zoom level 1에서 BOTTOMLEFT 적의 y좌표가 450이라서 거기까지 이동
		// 좌표에 zoom level을 곱해서 가변적인 좌표를 얻음
		if (enemy->pos.y >= 450)
		{
			enemy->enemyPosition = BOTTOMLEFT;
		}
	}
	if (enemy->enemyPosition == BOTTOMLEFT)
	{
		enemy->pos.x += dt * (17.f/9.f);
		if (enemy->pos.x >= 850)
		{
			enemy->enemyPosition = BOTTOMRIGHT;
		}
	}
	if (enemy->enemyPosition == BOTTOMRIGHT)
	{
		enemy->pos.y -= dt;
		if (enemy->pos.y <= -450)
		{
			enemy->enemyPosition = TOPRIGHT;
		}
	}
	if (enemy->enemyPosition == TOPRIGHT)
	{
		enemy->pos.x -= dt * (17.f / 9.f);
		if (enemy->pos.x <= -850)
		{
			enemy->enemyPosition = TOPLEFT;
		}
	}
}

// 시간을 재서 Time > Delay면 탄을 발사하는 함수 만들거임
void BulletConditioner(Enemy* e, Bullet* b)
{
	float dt = GetDt();
	e->fireTime += dt;
	if (e->fireDelay <= e->fireTime)
	{
		e->fireTime = 0.f;
		b[e->magazine].active = 1;
		e->magazine++;

	}
	if (e->magazine >= MAX_BULLETS_PER_ENEMY)
	{
		e->magazine = 0;
	}
}

// 원형 발사 패턴
// 탄환의 position을 업데이트 해주고 Draw도 해줌
// 탄환의 개수는 MAX_BULLETS_PER_ENEMY 만큼 있어야 함 
void CircleBulletFire(Enemy* e, Bullet* b)
{
	float dt = GetDt();
	for (int i = 0; i < MAX_BULLETS_PER_ENEMY; i++)
	{
		float originX = e->pos.x;
		float originY = e->pos.y;
		b[i].projTime += dt;
		if (!b[i].active)
		{
			b[i].projPos.x = originX;
			b[i].projPos.y = originY;
			b[i].fireAngle = CP_Math_Radians(b[i].degree);
			b[i].fireDir.x = cosf(b[i].fireAngle);
			b[i].fireDir.y = sinf(b[i].fireAngle);
			b[i].active = 1;
		}
		else
		{
			b[i].projPos.x += b[i].projSpd * b[i].fireDir.x * dt;
			b[i].projPos.y += b[i].projSpd * b[i].fireDir.y * dt;
			b[i].degree += 360.f / MAX_BULLETS_PER_ENEMY;
			CP_Settings_Fill(CP_Color_Create(238, 1, 147, 255));
		}
		if (b[i].projTime > e->fireDelay)
		{
			b[i].active = 0;
			b[i].projTime = 0;
			b[i].projPos.x = originX;
			b[i].projPos.y = originY;
		}
	}
}

// 발사 시점 플레이어 위치로 직진하는 탄환 발사
// 탄환의 position 업데이트 및 탄환 Draw
// e: 탄환의 origin position, 발사 방향을 구하기 위한 Enemy 정보
// b: Enemy.c에서 초기화한 탄환 배열: 탄환의 position 업데이트, position 기반 렌더링에 사용할
//탄환 정보
void DirectBulletFire(Enemy* e, Bullet* b)
{
	float dt = GetDt();

	for (int i = 0; i < MAX_BULLETS_PER_ENEMY; i++)
	{
		if (!b[i].active)
		{
			b[i].projPos.x = e->pos.x;
			b[i].projPos.y = e->pos.y;
			b[i].fireDir = CP_Vector_Subtract(player->pos, e->pos);
			b[i].direction = CP_Vector_Normalize(b[i].fireDir);
		}
		if (b[i].active)
		{
			// 방향 정규화 할 거임
			b[i].projPos.x += b[i].projSpd * b[i].direction.x * dt;
			b[i].projPos.y += b[i].projSpd * b[i].direction.y * dt;
		}
	}
}

void LaserInit()
{

}

int LaserAlpha = 50; // 전조 알파값
int LaserAlphaMax = 125; // 전조 최대 알파값
float LaserTimer = 0.f; // 전조 시간
float LaserChargeTime = 1.5f; // 전조 시간 cap
float LaserChargeWidth = 0.f; // 전조 범위
float LaserWidth = 150.f; // 전조 범위 cap
float LaserAttackTimer = 0.f; // 공격 시간
float LaserTime = 1.f; // 공격 시간 cap
float LaserDelay = 0.5f; // 전조 후 발사 전 사라질 시간 cap
float LaserDelayTimer = 0.f; // 사라질 시간

void LaserAttack()
{
	CamInfo* cam = GetCamera();
	CP_Matrix pcS;
	pcS = CP_Matrix_Scale(CP_Vector_Set(cam->camZoom, cam->camZoom));
	CP_Matrix pcT;
	pcT = CP_Matrix_Translate(cam->camPos);

	float dt = CP_System_GetDt();
	if (LaserTimer > LaserChargeTime && LaserAttackTimer > LaserTime)
	{
		LaserTimer = 0.f;
		LaserAttackTimer = 0.f;
		LaserChargeWidth = 0.f;
		LaserDelayTimer = 0.f;
	}
	if (LaserTimer < LaserChargeTime)
	{
		LaserTimer += dt * 1.5f;
		LaserChargeWidth += dt * 100.f;
		LaserAlpha = (int)(LaserTimer / LaserChargeTime * LaserAlphaMax);
		if (LaserAlpha > LaserAlphaMax) LaserAlpha = LaserAlphaMax;
		if (LaserChargeWidth > LaserWidth) LaserChargeWidth = LaserWidth;
		CP_Settings_Fill(CP_Color_Create(238, 1, 147, LaserAlpha));
		CP_Settings_NoStroke();
		CP_Graphics_DrawRect(WIDTH / 2, HEIGHT / 2, LaserChargeWidth * cam->camZoom, HEIGHT / cam->camZoom); // 레이저 위치
	}
	else if (LaserDelayTimer < LaserDelay)
	{
		LaserDelayTimer += dt;
	}
	else
	{
		LaserAttackTimer += dt;
		if (LaserAttackTimer < LaserTime)
		{
			CP_Settings_Fill(CP_Color_Create(238, 1, 147, 255));
			CP_Graphics_DrawRect(WIDTH / 2, HEIGHT / 2, 100 * cam->camZoom, HEIGHT / cam->camZoom);
		}
	}
}

void DisableEnemy(Enemy* _enemy)
{
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		_enemy[i].active = 0;
	}
}
