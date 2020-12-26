#pragma once
#include "CGameObject.h"

class CMarioIcon : public CGameObject
{
private:
	float posXGoingTo, posYGoingTo;
	bool isMoving;
public:
	CMarioIcon();
	void MoveToCell(int x, int y, bool instant = true);
	virtual void Render() override;
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) override;
};