#pragma once
#include "CGameObject.h"

class CGoomba : public CGameObject
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	CGoomba();
	virtual void SetState(int state);
};