#pragma once
#include "CGameObject.h"

class Tail : public CGameObject
{
public:
	bool isHiting;
	Tail();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void OnCollisionEnter(LPCOLLISIONEVENT other);
	void Render();
};