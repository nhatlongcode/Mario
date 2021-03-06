#pragma once
#include "CRewardObject.h"
#include "CScoreFx.h"

class CCoin : public CRewardObject
{
private:
	int startTime = -1;
	CSCoreFx* scoreFx;
	bool bounceDone;
public:
	CCoin();
	void TriggerReward() override;
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void SetState(int state);
	void Render();
};