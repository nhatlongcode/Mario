#include "CAnimation.h"

CAnimation::CAnimation(int defaultTime)
{
	this->defaultTime = defaultTime;
	currentFrame = -1;
	lastFrameTime = -1;
}

void CAnimation::Add(int spriteId, DWORD time)
{

}
