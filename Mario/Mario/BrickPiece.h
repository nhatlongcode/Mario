#pragma once
#include "CGameObject.h"

class BrickPiece : public CGameObject
{
private:
	float bounceX;
	float bounceY;
	LPSPRITE sprite;
	bool isBreaked;
public:
	BrickPiece();
	void Break();
	void SetBounceBreak(float vx, float vy, int nx);
	void SetSprite(int id);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void SetState(int state) override;
	virtual void Render() override;
};