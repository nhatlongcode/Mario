#include "CAnimationsManager.h"
#include "Utils.h"

void CAnimationsManager::Add(int id, LPANIMATION ani)
{
	animations[id] = ani;
	DebugOut(L"ANIM ID: %d ADDED \n", id);
}

LPANIMATION CAnimationsManager::Get(int id)
{
	return animations[id];
}

void CAnimationsManager::Clear()
{
	for (auto x : animations)
	{
		auto element = x.second;
		if (element != nullptr) delete element;
	}
	animations.clear();
}
