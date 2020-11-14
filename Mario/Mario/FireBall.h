#pragma once
#include "CGameObject.h"

class FireBall : public CGameObject
{
public:
	long explodeStart = 0;
	FireBall(float x, float y, int direction);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	void OnCollisionEnter(LPCOLLISIONEVENT other);
	void StartExplode();
};