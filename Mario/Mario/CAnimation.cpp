#include "CAnimation.h"
#include "Utils.h"

void CAnimation::Add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;

	LPSPRITE sprite = CLocator<ISpritesManager>().Get()->Get(spriteId);

	if (sprite == NULL)
	{
		DebugOut(L"[ERROR] Sprite ID %d cannot be found!\n", spriteId);
	}

	LPFRAME frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}

void CAnimation::Render(float x, float y, int direction, float speed, int alpha)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		t = t / speed;
		//DebugOut(L"%ld",t);
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) currentFrame = 0;
		}
	}

	frames[currentFrame]->GetSprite()->Draw(x, y, direction, alpha);
}

void CAnimation::Render(float x, float y, int direction, int runTime, int totalTime, D3DXCOLOR overlay)
{
	int frameIndex = max(0, min(trunc(runTime / (totalTime / frames.size())), frames.size() - 1));

	frames[frameIndex]->GetSprite()->Draw(x, y, direction);
}
