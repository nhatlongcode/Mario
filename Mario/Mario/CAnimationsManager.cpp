#include "CAnimationsManager.h"


void CAnimationsManager::Add(int id, LPANIMATION ani)
{
	animations[id] = ani;
}

LPANIMATION CAnimationsManager::Get(int id)
{
	return animations[id];
}
