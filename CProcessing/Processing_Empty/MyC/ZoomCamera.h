#pragma once
#include "cprocessing_common.h"
#include "../Defines.h"
typedef struct CamInfo
{
	CP_Matrix camMatrix;
	CP_Vector camPos;
	float camZoom;
} CamInfo;

void InitCamera();
CamInfo* GetCamera();
void SetZoom(StageState stage);
void ZoomIn();
void ZoomOut();
void DestroyCam();
void ZoomOutSlightly(float);
void ZoomInSlightly(float);
void SetZoomOutTargetRate();
void SetZoomInTargetRate();
void ZoomInForce();
void ZoomOutForce();

void CameraShaking();
void ResetCameraShakeTime();

void CameraMove(LaserDirection _direction, float speed,float targetTime);

