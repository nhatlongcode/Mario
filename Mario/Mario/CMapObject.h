#pragma once
#include "CGameObject.h"

class CMapObject : public CGameObject
{
private:
	int index;
public:
	CMapObject();
	void MoveToCell(int x, int y);
	void SetIndex(int index);
	int GetIndex();
	virtual void Render() override;
};