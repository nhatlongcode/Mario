#pragma once
#include "CGameObject.h"

class CGoomba : public CGameObject
{
public:
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	CGoomba();
	virtual void SetState(int state);
};