#ifndef CANIMATION_H
#define CANIMATION_H

#include "CAnimationFrame.h"
#include "CSprite.h"
#include "CLocator.h"
class CAnimation
{
private:
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	std::vector<LPFRAME> frames;
public:
	CAnimation(int defaultTime);
	void Add(int spriteId, DWORD time = 0);
	void Render(float x, float y);
};
#endif

