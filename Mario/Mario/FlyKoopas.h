#pragma once
#include "CGameObject.h"

class FlyKoopas : public CGameObject
{
private:
	int startTime = -1, timeOnShell = -1;
	bool isGround;
	bool isBeingHold;
public:
	FlyKoopas();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void SetHoldByMario(bool hold);
	void Render();
	void SetState(int state);
	void OnCollisionEnter(LPCOLLISIONEVENT other);
	virtual bool GetThrought(ObjectTag tag, float nx, float ny) override;
};