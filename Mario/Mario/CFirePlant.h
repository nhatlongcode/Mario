#pragma once
#include "CGameObject.h"
#include "CFireFromPlant.h"

class CFirePlant : public CGameObject
{
private:
	bool isGoDown;
	bool isGoUp;
	bool fired;
	CFireFromPlant* fireBall;
	int steps;
	int startFire;
	float goOutDist, startY;
	int coolDownFire;
public:
	CFirePlant();
	void Fire();
	// Inherited via CGameObject
	virtual void Render() override;
	virtual void SetState(int state) override;
	void OnCollisionEnter(LPCOLLISIONEVENT other) override;
	virtual bool GetThrought(ObjectTag tag, float nx, float ny) override;
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) override;
};

