#pragma once
#include "CGameObject.h"

class CKoopas : public CGameObject
{
private:
public:
	CKoopas();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void OnCollisionEnter(LPCOLLISIONEVENT other);
};