#include "CMapObject.h"

CMapObject::CMapObject() : CGameObject()
{
	index = 0;
	IsCollisionEnabled = false;
}

void CMapObject::MoveToCell(int x, int y)
{
	float posY = float(y * 48);
	float posX = float(x * 48);
	SetPosition(posX, posY);
}

void CMapObject::SetIndex(int index)
{
	this->index = index;
	state = index;
}

int CMapObject::GetIndex()
{
	return index;
}

void CMapObject::Render()
{
	if (state > animSet->size()) return;
	animSet->at(state)->Render(x,y,1,1,alpha);
}
