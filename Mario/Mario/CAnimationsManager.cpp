#include "CAnimationsManager.h"

void CAnimationsManager::LoadResources()
{
	LPANIMATION ani = new CAnimation(100);
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);

	Add(500, ani);

	ani = new CAnimation(100);
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	Add(501, ani);
}

void CAnimationsManager::Add(int id, LPANIMATION ani)
{
	animations[id] = ani;
}

LPANIMATION CAnimationsManager::Get(int id)
{
	return animations[id];
}
