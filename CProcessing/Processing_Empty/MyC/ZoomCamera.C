#include "ZoomCamera.h"
#include "math.h"
#include "unit.h"

float nowZoomSize;

void InitCamera()
{
	nowZoomSize = 1.0f;
}


void ZoomIn()
{
	nowZoomSize * 1.25f;

	// 소수점 둘째자리까지 반올림
	round(nowZoomSize * 100) / 100);
}
void ZoomOut()
{
	nowZoomSize / 1.25f;
	round(nowZoomSize * 100) / 100);


}