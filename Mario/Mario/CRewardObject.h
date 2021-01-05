#pragma once
#include "CGameObject.h"

class CRewardObject : public CGameObject
{
public:
	virtual void TriggerReward() { } 
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override { };
	virtual void Render() override { };
};