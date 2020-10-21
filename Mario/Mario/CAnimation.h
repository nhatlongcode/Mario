#pragma once
#include "CAnimationFrame.h"
#include "CSpritesManager.h"
#include "CLocator.h"
class CAnimation
{
	DWORD lastFrameTime;
	int currentFrame;
	int defaultTime;
	vector<LPFRAME> frames;
public:
	CAnimation(int defaultTime = 100) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void Add(int spriteId, DWORD time = 0);

	void Render(float x, float y, int direction = DIRECTION_RIGHT, int alpha = 255);
};
typedef CAnimation* LPANIMATION;
typedef vector<LPANIMATION> CAnimSet;
typedef CAnimSet* LPANIM_SET;
