#pragma once
#include "CGameObject.h"

class CSCoreFx : public CGameObject
{
private:
	int startTime;
	bool effectDone;
	bool effectBegin;
public:
	CSCoreFx(int scoreState = 0);
	bool IsEffectBegin();
	void BeginEffect();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void SetScoreState(int scoreState);
	void ResetEffect();
	// Inherited via CGameObject
	virtual void Render() override;
};