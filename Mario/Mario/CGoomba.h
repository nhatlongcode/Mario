#pragma once
#include "CGameObject.h"

class CGoomba : public CGameObject
{
public:

	CGoomba();
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void SetState(int state);
};