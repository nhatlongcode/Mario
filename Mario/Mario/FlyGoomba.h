#pragma once
#include "CGameObject.h"

class FlyGoomba : public CGameObject
{
private:
	bool isGround;
	int step;
public:
	// Inherited via CGameObject
	FlyGoomba();
	virtual void Render() override;
	void SetState(int state) override;
	void OnCollisionEnter(LPCOLLISIONEVENT other) override;
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) override;
};