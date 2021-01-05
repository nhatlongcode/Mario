#pragma once
#include "CRewardObject.h"
class CMushroom : public CRewardObject
{
private:
	int startTime = -1;
	bool isOutOfBrick = false;
public:
	CMushroom();
	void TriggerReward() override;
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void SetState(int state);
	void Render();
	void OnCollisionEnter(LPCOLLISIONEVENT other) override;
};