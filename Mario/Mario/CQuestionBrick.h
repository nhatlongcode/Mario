#pragma once

#include <queue>
#include "CGameObject.h"
#include "Enum.h"

class CRewardObject;

class CQuestionBrick : public CGameObject
{
private:
	queue<BrickObjectTag> listReward;
	BrickObjectTag rewardTag;
	CRewardObject* reward;
	long bounceBegin = -1;
	float beginY;
public:
	CQuestionBrick();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void SetBrickReward(BrickObjectTag reward);

	void AddBrickReward(BrickObjectTag id);
	void TriggerBrick();

	void SetState(int state);
	void Bounce();
	void Render();
};