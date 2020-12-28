#pragma once
#include "CGameObject.h"
#include "Enum.h"
#include "CCoin.h"

class CQuestionBrick : public CGameObject
{
private:
	BrickObjectTag reward;
	CCoin* coin;
	long bounceBegin = -1;
	float beginY;
public:
	CQuestionBrick();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void SetBrickReward(BrickObjectTag reward);
	void SetState(int state);
	void Bounce();
	void Render();
};