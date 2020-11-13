#pragma once
#include "CAnimationFrame.h"
#include "CSpritesManager.h"
#include "CLocator.h"
class CAnimation
{
private:
	DWORD lastFrameTime;
	int currentFrame;
	int defaultTime;
	bool isRepeat;
	vector<LPFRAME> frames;
public:
	CAnimation(int defaultTime = 100, bool isRepeat = false);
	void Add(int spriteId, DWORD time = 0);

	void Render(float x, float y, int direction = DIRECTION_RIGHT, float speed = 1.0f, int alpha = 255);
	void Render(float x, float y, int direction, int runTime, int totalTime, D3DXCOLOR overlay);

};
typedef CAnimation* LPANIMATION;
typedef vector<LPANIMATION> CAnimSet;
typedef CAnimSet* LPANIMSET;
