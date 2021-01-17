#pragma once
#include "CGameObject.h"

class CFireFromPlant : public CGameObject
{
private:

public:
	CFireFromPlant(float x, float y, int direction);
	// Inherited via CGameObject
	virtual void Render() override;
	virtual void SetState(int state) override;
	void OnCollisionEnter(LPCOLLISIONEVENT other);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual bool GetThrought(ObjectTag tag, float nx, float ny) override;
};