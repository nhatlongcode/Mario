#pragma once
#include "CGameObject.h"

class CGoomba : public CGameObject
{
public:

	CGoomba();
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual bool GetThrought(ObjectTag tag, float nx, float ny) override;
	void SetState(int state);
};