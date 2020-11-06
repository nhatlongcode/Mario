#pragma once
#include "CGameObject.h"

class CBrick : public CGameObject
{
public:
	CBrick();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
};