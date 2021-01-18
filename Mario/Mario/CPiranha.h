#pragma once
#include "CGameObject.h"

class CPiranha : public CGameObject
{
private:
	int steps;
	int stayTime;
	int startY;
	LPSPRITE coverPipe;
public:

	CPiranha();
	virtual void Render() override;
	virtual void SetState(int state) override;
	void SetCoverPipe(int id);
	void OnCollisionEnter(LPCOLLISIONEVENT other) override;
	virtual bool GetThrought(ObjectTag tag, float nx, float ny) override;
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) override;

};