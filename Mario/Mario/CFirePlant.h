#pragma once
#include "CGameObject.h"

class CFirePlant : public CGameObject
{
private:
public:
	CFirePlant();
	// Inherited via CGameObject
	virtual void Render() override;
	virtual void SetState(int state) override;
	void OnCollisionEnter(LPCOLLISIONEVENT other) override;
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) override;
};

