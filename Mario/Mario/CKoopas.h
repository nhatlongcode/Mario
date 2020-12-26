#pragma once
#include "CGameObject.h"

class CKoopas : public CGameObject
{
private:
	int startTime = -1, timeOnShell = -1;
public:
	CKoopas();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void OnCollisionEnter(LPCOLLISIONEVENT other);
};