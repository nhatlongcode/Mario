#pragma once
#include "CGameObject.h"

class BrickPiece : public CGameObject
{
private:
	LPSPRITE sprite;
	bool isBreaked;
public:
	BrickPiece();
	void SetSprite(int id);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render() override;
};