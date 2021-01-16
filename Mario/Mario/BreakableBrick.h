#pragma once
#include "CGameObject.h"
#include "BrickPiece.h"

class BreakableBrick : public CGameObject
{
private:
	bool isBreaked;
	bool pButton;
	vector<BrickPiece*> pieces;
public:
	BreakableBrick();
	virtual void Render() override;
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void SetState(int state);
	void OnCollisionEnter(LPCOLLISIONEVENT other);
	void Break();
};