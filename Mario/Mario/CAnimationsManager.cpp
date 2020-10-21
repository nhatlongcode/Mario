#include "CAnimationsManager.h"


void CAnimationsManager::Add(int id, LPANIMATION ani)
{
	animations[id] = ani;
}

LPANIMATION CAnimationsManager::Get(int id)
{
	return animations[id];
}

void CAnimationsManager::Clear()
{
	for (auto x : animations)
	{
		LPANIMATION ani = x.second;
		delete ani;
	}

	animations.clear();
}
