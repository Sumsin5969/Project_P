#pragma once
#include "cprocessing_common.h"

typedef struct CamInfo
{
	CP_Matrix camMatrix;
	CP_Vector camPos;
	float camZoom;
} CamInfo;

void InitCamera();
CamInfo* GetCamera();
void ZoomIn();
void ZoomOut();
void DestroyCam();
void ZoomOutSlightly(float);
void ZoomInSlightly(float);
void SetZoomOutTargetRate();
void SetZoomInTargetRate();
void ZoomInForce();
void ZoomOutForce();

