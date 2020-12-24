#pragma once
#include "CGameObject.h"

class CMarioIcon : public CGameObject
{
private:

public:
	CMarioIcon();
	void MoveToCell(int x, int y);
	virtual void Render() override;
};