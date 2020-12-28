#pragma once
#include "CGameObject.h"
#include "CScoreFx.h"

class CCoin : public CGameObject
{
private:
	int startTime = -1;
	CSCoreFx* scoreFx;
	bool bounceDone;
public:
	CCoin();
	void Bounce();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void SetState(int state);
	bool GetBounceDone();
	void Render();
};